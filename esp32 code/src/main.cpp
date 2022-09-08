// Standard libraries
#include <Arduino.h>
#include <esp_task_wdt.h>

// WiFi
#include <WiFi.h>
#include "credentials.hpp"

// SD-Card
#include <SPI.h>
#include <SD.h>

// GPS, ThingSpeak
#include "UtilGPS.hpp"
#include <SoftwareSerial.h>
#include "ThingSpeak.h"

#define RX_PIN 16
#define TX_PIN 17

#define WATCHDOG_TIMEOUT_S 30
#define WIFI_TIMEOUT_MS 20000
#define THINGSPEAK_TIMEOUT_MS 20000

WiFiClient client;
File myFile;
TinyGPSPlus gps;                          // TinyGPS++ object
UtilGPS myGPS;
SoftwareSerial ss(RX_PIN, TX_PIN);        // Serial connection to the GPS device.

// Save last ThingSpeak request
unsigned long lastMS; 

// connectWifiTask: Maintain wifi connection
void connectWifiTask (void * parameters) {
  esp_task_wdt_init(WATCHDOG_TIMEOUT_S, false);
  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      vTaskDelay(10000 / portTICK_PERIOD_MS);
      continue;
    }
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssidPhone, passwordPhone);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS) { }

    if (WiFi.status() != WL_CONNECTED) { vTaskDelay(20000 / portTICK_PERIOD_MS); }
  }
}

// Get number of data entries in SD
int countSDEntries() {
  int numEntries = 0;

  while (myFile.available()) {
    char buffer = myFile.read();
    if (buffer == '\n') numEntries++;
  }
  myFile.seek(0);

  return numEntries;
}

// Log each field to ThingSpeak
void writeToThingSpeak() {
  ThingSpeak.begin(client);

  ThingSpeak.setField(1, myGPS.getLatitude());
  ThingSpeak.setField(2, myGPS.getLongitude());
  ThingSpeak.setField(3, myGPS.getTimestamp());
  ThingSpeak.setField(4, myGPS.getDate());
  ThingSpeak.setField(5, myGPS.getSpeed());

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
}

void parseDataEntry(String entry) {
  String entryByDelimiter[5];

  for (int i = 0; i < 4; i++) {
    unsigned long delimiter = entry.indexOf('|');
    entryByDelimiter[i] = entry.substring(0, delimiter);
    entry = entry.substring(delimiter + 1, entry.length());
  }
  entryByDelimiter[4] = entry;

  myGPS.setGPSValues(entryByDelimiter[0], entryByDelimiter[1], entryByDelimiter[2], entryByDelimiter[3], entryByDelimiter[4]);
}

// Offload SD data to ThingSpeak
void offloadSD() {
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS) { }

  if (WiFi.status() == WL_CONNECTED) {
    myFile = SD.open("/datalog.txt", FILE_READ);

    int entryLimit = countSDEntries();
    for (int i = 0; i < entryLimit; i++) {
      String buffer = myFile.readStringUntil('%');
      parseDataEntry(buffer);
      writeToThingSpeak();
      delay(THINGSPEAK_TIMEOUT_MS);
    }

    myFile.close();
    SD.remove("/datalog.txt");
  }
}

// Log each field to SD-Card
void writeToSD() {
  myFile = SD.open("/datalog.txt", FILE_APPEND);

  if (myFile) {
    String dataGPS = myGPS.getLatitude() + "|" + myGPS.getLongitude() + "|" + myGPS.getTimestamp() + "|" + myGPS.getDate() + "|" + myGPS.getSpeed() + "%";
    myFile.println(dataGPS);
  }
  
  myFile.close();
}

void setup() {
  Serial.begin(115200);
  ss.begin(9600);

  if (!SD.begin()) {
    Serial.println("SD-Card initialization failed");
    while (1);
  }
  Serial.println("SD-Card initialization done");

  WiFi.mode(WIFI_STA);

  /*Syntax for assigning task to a core:
  xTaskCreatePinnedToCore(
                  coreTask,       // Function to implement the task
                  "coreTask",     // Name of the task 
                  10000,          // Stack size in words 
                  NULL,           // Task input parameter 
                  0,              // Priority of the task 
                  NULL,           // Task handle. 
                  taskCore);      // Core where the task should run 
  */
  
  xTaskCreatePinnedToCore(connectWifiTask, "connectWifiTask", 5000, NULL, 1, NULL, 0);        
  delay(500); 

  offloadSD();

  // Create a fresh datalog.txt file
  if (!(SD.exists("/datalog.txt"))) {
    myFile = SD.open("/datalog.txt", FILE_WRITE);
    myFile.close();
  }
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      myGPS.updateLocation(gps);
      myGPS.updateDate(gps);
      myGPS.updateTimestamp(gps);
      myGPS.updateSpeed(gps);
      // All invalid gps data will still store previous valid data
      if (WiFi.status() == WL_CONNECTED) { Serial.println("Connected to internet"); }
      else { Serial.println("Disconnected"); }
      myGPS.printGPSValues();
    }
  }

  if (millis() - lastMS >= THINGSPEAK_TIMEOUT_MS) {
    if (WiFi.status() == WL_CONNECTED) { writeToThingSpeak(); }
    else { writeToSD(); }
    lastMS = millis();
  }
}