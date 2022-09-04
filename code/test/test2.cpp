#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "ThingSpeak.h"

WiFiClient client;            // WiFi object
TinyGPSPlus gps;              // TinyGPS++ object
SoftwareSerial ss(4, 5) ;     // Serial connection to the GPS device.

const char ssid[] = "Nguyen_family24";          // Your network SSID (name)
const char password[] = "5648936kng24";         // Your network password
char myWriteAPIKey[] = "MX7V3BXSAB153H10";      // Your ThingSpeak API-key

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void startWiFi() {
  WiFi.begin(ssid, password);
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
  Serial.begin(115200);
  ss.begin(9600);

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  startWiFi();
}



void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      String latitude = String(gps.location.lat(), 6);
      String longitude = String(gps.location.lng(), 6);

      //  Serial.println(theNum.substring(splitIndex));
  // theNum.remove(splitIndex);
  // Serial.println(theNum);

      Serial.print("Latitude: ");
      Serial.println(latitude);
      Serial.print("Longitude: ");
      Serial.println(longitude);
      Serial.println("");
      delay(3000);
    }
  }
}