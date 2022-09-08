#ifndef UtilGPS_h
#define UtilGPS_h

#include <Arduino.h>
#include <TinyGPS++.h>

class UtilGPS {
  public:

    UtilGPS();

    // Getters
    String getLatitude();
    String getLongitude();
    String getDate();
    String getTimestamp();
    String getSpeed();

    // Setters
    void setGPSValues(String aLatitude, String aLongitude, String aDate, String aTimestamp, String aSpeed);

    void printGPSValues();

    void updateLocation(TinyGPSPlus mGPS);
    void updateDate(TinyGPSPlus mGPS);
    void updateTimestamp(TinyGPSPlus mGPS);
    void updateSpeed(TinyGPSPlus mGPS);

  protected:
    String latitude, longitude, date, timestamp, speed;

};

#endif /* UtilGPS_hpp */