#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("/datalog.txt", FILE_READ);

  while (myFile.available()) {
    Serial.write(myFile.read());
    Serial.println("\n");
  }
  
}

void loop() {
  // nothing happens after setup
}