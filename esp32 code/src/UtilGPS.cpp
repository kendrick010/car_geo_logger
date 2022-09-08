#include "UtilGPS.hpp"

UtilGPS::UtilGPS() {
  latitude = "0.0";
  longitude = "0.0";
  date = "0.0";
  timestamp = "0.0";
  speed = "0.0";
}

String UtilGPS::getLatitude() { return latitude; }
String UtilGPS::getLongitude() { return longitude; }
String UtilGPS::getDate() { return date; }
String UtilGPS::getTimestamp() { return timestamp; }
String UtilGPS::getSpeed() { return speed; }

void UtilGPS::setGPSValues(String aLatitude, String aLongitude, String aDate, String aTimestamp, String aSpeed) {
  latitude = aLatitude;
  longitude = aLongitude;
  date = aDate;
  timestamp = aTimestamp;
  speed = aSpeed;
}

void UtilGPS::printGPSValues() {
  Serial.println("Latitude: " + latitude);
  Serial.println("Longitude: " + longitude);
  Serial.println("Date: " + date);
  //Serial.println("Time: " + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()));
  Serial.println("Time: " + timestamp);
  Serial.println("Speed: " + speed);
  Serial.println("\n");
}

void UtilGPS::updateLocation(TinyGPSPlus mGPS) {
  if (mGPS.location.isValid()) {
    // Truncate to first 6-digits of latitude and longitude
    latitude = String(mGPS.location.lat(), 6);
    longitude = String(mGPS.location.lng(), 6);
  }
}

void UtilGPS::updateDate(TinyGPSPlus mGPS) {
  if (mGPS.date.isValid()) {
    // Get UST date, format to float of month.day
    date = String(mGPS.date.month()) + "." + String(mGPS.date.day());
  }
}

void UtilGPS::updateTimestamp(TinyGPSPlus mGPS) {
  if (mGPS.time.isValid()) {
    // Get UST time, format to purely seconds in day
    int hourToSeconds = mGPS.time.hour() * 60 * 60;
    int minuteToSeconds = mGPS.time.minute() * 60;
    int seconds = hourToSeconds + minuteToSeconds + mGPS.time.second();
    timestamp = String(seconds);
  }
}

void UtilGPS::updateSpeed(TinyGPSPlus mGPS) {
  if (mGPS.speed.isValid()) {
    // Get speed in mph
    speed = String(mGPS.speed.mph());
  }
}