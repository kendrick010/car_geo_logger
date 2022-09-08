#ifndef UtilGPS_h
#define UtilGPS_h

#include <Arduino.h>
#include <TinyGPS++.h>

// Custom TinyGPS++ wrapper
class UtilGPS {

  public:
    // Ctor
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

    // Update GPS members with new readings
    void updateLocation(TinyGPSPlus mGPS);
    void updateDate(TinyGPSPlus mGPS);
    void updateTimestamp(TinyGPSPlus mGPS);
    void updateSpeed(TinyGPSPlus mGPS);

  protected:
    // GPS members
    String latitude, longitude, date, timestamp, speed;

};

#endif /* UtilGPS_hpp */