#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = D8;
char ssid[] = "UCSD-GUEST";         // your network SSID (name)
char password[] = "password";     // your network password

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
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(chipSelect, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed.");
    while (true);
  }

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("Hello");
    dataFile.close();
    // print to the serial port too:
    Serial.println("Hello");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  // wifiSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
}