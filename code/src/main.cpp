#include "SPI.h"
#include <SD.h>

const int chipSelect = D8;
File myFile;

void write_text() {
  myFile = SD.open("data_log.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to data_log.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data_log.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("data_log.txt");
  if (myFile) {
    Serial.println("data_log.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data_log.txt");
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect, HIGH);

  Serial.print("\r\nWaiting for SD card to initialise...");
  if (!SD.begin(chipSelect)) { // CS is D8 in this example
    Serial.println("Initialising failed!");
    return;
  }
  Serial.println("Initialisation completed");
}

void loop() {
  // nothing happens after setup finishes.
}