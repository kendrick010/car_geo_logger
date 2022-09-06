// GPS library
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;                // TinyGPS++ object
SoftwareSerial ss(16, 17);      // Serial connection to the GPS device.

String latitude = "0.0", longitude = "0.0";
String date = "0.0";
String timeRecord = "0.0";
String speed = "0.0";

void printGPSData() {
  Serial.println("Latitude: " + latitude);
  Serial.println("Longitude: " + longitude);
  Serial.println("Date: " + date);
  //Serial.println("Time: " + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()));
  Serial.println("Time: " + timeRecord);
  Serial.println("Speed: " + speed);
  Serial.println("\n");
}

void getLocation() {
  if (gps.location.isValid()) {
    // Truncate to first 6-digits of latitude and longitude
    latitude = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
  }
}

void getDate() {
  if (gps.date.isValid()) {
    // Get UST date, format to float of month.day
    date = String(gps.date.month()) + "." + String(gps.date.day());
  }
}

void getTime() {
  if (gps.time.isValid()) {
    // Get UST time, format to purely seconds in day
    int hourToSeconds = gps.time.hour() * 60 * 60;
    int minuteToSeconds = gps.time.minute() * 60;
    int seconds = hourToSeconds + minuteToSeconds + gps.time.second();
    timeRecord = String(seconds);
  }
}

void getSpeed() {
  if (gps.speed.isValid()) {
    // Get speed in mph
    speed = String(gps.speed.mph());
  }
}