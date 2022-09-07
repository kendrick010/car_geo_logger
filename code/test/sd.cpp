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


  // Create temp text file for copying
  myFile = SD.open("/templog.txt", FILE_WRITE);
  myFile.close();

  // Store first entry
  myFile = SD.open("/datalog.txt", FILE_READ);
  int entryLimiter = countSDEntries() - 1;
  String lista = myFile.readStringUntil('\n');
  unsigned long start = myFile.position();
  myFile.close();

  for (int i = 0; i < entryLimiter; i++) {
    myFile = SD.open("/datalog.txt", FILE_READ);
    myFile.seek(start);
    String entry = myFile.readStringUntil('\n');
    start = myFile.position();
    myFile.close();

    myFile = SD.open("/templog.txt", FILE_APPEND);
    myFile.print(entry);
    myFile.close();
  }

  SD.remove("/datalog.txt");

  myFile = SD.open("/templog.txt");
  while (myFile.available()) {
    Serial.println(myFile.read());
  }
  myFile.close();
  

  
}

void loop() {
  // nothing happens after setup
}