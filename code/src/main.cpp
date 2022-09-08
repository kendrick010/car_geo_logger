#include <SPI.h>
#include <SD.h>

File myFile;

int countSDEntries() {
  int numEntries = 0;

  while (myFile.available()) {
    char buffer = myFile.read();
    if (buffer == '\n') numEntries++;
  }
  myFile.seek(0);

  return numEntries;
}

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

  // Store first entry
  myFile = SD.open("/datalog.txt", FILE_READ);

  String buffer = myFile.readStringUntil('%');

  myFile.close();
  

  
}

void loop() {
  // nothing happens after setup
}