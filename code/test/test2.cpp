// Standard libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "credentials.h"

// GPS library
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// SD-Card library
#include <SPI.h>
#include <SD.h>

// ThingSpeak API library
#include "ThingSpeak.h"

WiFiClient client;            // WiFi object
TinyGPSPlus gps;              // TinyGPS++ object
SoftwareSerial ss(4, 5);     // Serial connection to the GPS device.

// Timer variables
unsigned long delayBetweenRequests = 60000;     // Time between requests (1 minute) 
unsigned long requestDueTime;

const int chipSelect = D8;                // SD-Card module CS pin

// Connect to Wifi
void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, NULL);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(9600);

  pinMode(chipSelect, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD-Card initialization failed");
    while (true);
  }
  Serial.println("SD-Card initialization finished");

  wifiSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() > requestDueTime) {
    // do stuff
    requestDueTime = millis() + delayBetweenRequests;
  }
}