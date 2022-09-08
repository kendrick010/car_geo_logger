// Standard libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "credentials.h"

// SD-Card library
#include <SPI.h>
#include <SD.h>

// GPS library
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// ThingSpeak API library
#include "ThingSpeak.h"

WiFiClient client;            // WiFi object
TinyGPSPlus gps;              // TinyGPS++ object
SoftwareSerial ss(4, 5);      // Serial connection to the GPS device.

// Time between requests (30 seconds)
unsigned long delayBetweenRequests = 30000; 

// SD-Card module CS pin
const int chipSelect = D8;

String latitude = "0.0", longitude = "0.0";
String date = "0.0";
String timeRecord = "0.0";
String speed = "0.0";

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidMom, passwordMom);
}

void getLocation() {
  if (gps.location.isValid()) {
    // Truncate to first 6-digits of latitude and longitude
    latitude = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
    Serial.println("Latitude: " + latitude);
    Serial.println("Longitude: " + longitude);
  }
}

void getDate() {
  if (gps.date.isValid()) {
    // Get UST date, format to float of month.day
    date = String(gps.date.month()) + "." + String(gps.date.day());
    Serial.println("Date: " + date);
  }
}

void getTime() {
  if (gps.time.isValid()) {
    // Get UST time, format to purely seconds in day
    int hourToSeconds = gps.time.hour() * 60 * 60;
    int minuteToSeconds = gps.time.minute() * 60;
    int seconds = hourToSeconds + minuteToSeconds + gps.time.second();
    timeRecord = String(seconds);
    //Serial.println("Time: " + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()));
    Serial.println("Time: " + timeRecord);
  }
}

void getSpeed() {
  if (gps.speed.isValid()) {
    // Get speed
    speed = String(gps.speed.mph());
    Serial.print("Speed: " + speed);
    Serial.println("\n");
  }
}

void writeToThingSpeak() {
  // Log to each field
  ThingSpeak.setField(1, latitude);
  ThingSpeak.setField(2, longitude);
  ThingSpeak.setField(3, timeRecord);
  ThingSpeak.setField(4, date);
  ThingSpeak.setField(5, speed);

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
}

void storeToSD() {
  // Do nothing
}

void setup() {
  // Put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(9600);

  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect, HIGH);

  // Initialize SD-Card
  // if (!SD.begin(chipSelect)) {
  //   Serial.println("SD-Card initialization failed");
  //   while (true);
  // }
  // Serial.println("SD-Card initialization finished");
}

void loop() {
  // Put your main code here, to run repeatedly:
  while (ss.available() > 0) {
    unsigned long startElapsed = millis();

    // Attempt to connect to wifi, break after delayBetweenRequests
    //while (millis() - startElapsed < delayBetweenRequests) { connectWifi(); }
    if (WiFi.status() == WL_CONNECTED) Serial.println("Connected to Wifi!");

    // Read GPS data
    if (gps.encode(ss.read())) {
      getLocation();
      getDate();
      getTime();
      getSpeed();
      // All invalid gps data will still store previous valid data
    }

    // if(WiFi.status() != WL_CONNECTED) {
    //   // Store to ThingSpeak
    //   writeToThingSpeak();
    //   Serial.println("Sent to ThingSpeak");
    // }
    // else {
    //   // Store into SD-Card
    //   storeToSD();
    // }
    delay(1000);
  }
}