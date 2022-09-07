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

  myFile = SD.open("/templog.txt");
  int count = 0;
  while (myFile.available()) {
    // String entry = myFile.readStringUntil('\n');
    // Serial.print(entry);
    myFile.read();
    count++;
  }
  myFile.close();

  Serial.println(count);
  

  
}

void loop() {
  // nothing happens after setup
}