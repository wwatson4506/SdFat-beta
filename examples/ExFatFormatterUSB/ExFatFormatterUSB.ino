// Force exFAT formatting for all USB drives larger than 512MB.
//#include "SD.h"
#include "SdFat.h"

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
USBHub hub4(myusb);
msController msDrive1(myusb);
msController msDrive2(myusb);


SdExFat msc1;
//------------------------------------------------------------------------------
void errorHalt() {
  msc1.printSdError(&Serial);
  SysCall::halt();
}
#define error(s) (Serial.println(F(s)),errorHalt())
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  myusb.begin();

  Serial.println(F("Type any character to begin"));
  
  while (!Serial.available()) {
    yield();
  }
  do {
    delay(10);
  } while(Serial.read() >= 0);
  
  Serial.println();
  Serial.println(F(
    "Your SD will be formated exFAT.\r\n"
    "All data on the SD will be lost.\r\n"
    "Type 'Y' to continue.\r\n"));
    
  while (!Serial.available()) {
    yield();
  }
  if (Serial.read() != 'Y') {
    Serial.println(F("Exiting, 'Y' not typed."));
    return;
  }
  if (!msc1.cardBegin(&msDrive1)) {
    error("cardBegin failed");
  } else {
	Serial.println("Formatting USB drive to ExFat. Please wait...");
  }     
  if(!msc1.format(&Serial)) {
    error("format failed");
  }
  if (!msc1.volumeBegin()) {
    error("volumeBegin failed");
  }
  Serial.print(F("Bytes per cluster: "));
  Serial.println(msc1.bytesPerCluster());
  Serial.println(F("Done"));
}
void loop() {
}
