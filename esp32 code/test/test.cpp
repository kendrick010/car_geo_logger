// Standard libraries
#include <WiFi.h>
#include "credentials.h"

// GPS library
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;                // TinyGPS++ object
SoftwareSerial ss(16, 17);      // Serial connection to the GPS device.

String latitude = "0.0", longitude = "0.0";
String date = "0.0";
String timeRecord = "0.0";
String speed = "0.0";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidMom, passwordMom);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected!");
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

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  initWiFi();
}

void loop() {
  while (ss.available() > 0) {
    // Read GPS data
    if (gps.encode(ss.read())) {
      getLocation();
      getDate();
      getTime();
      getSpeed();
      // All invalid gps data will still store previous valid data
    }
  }
}