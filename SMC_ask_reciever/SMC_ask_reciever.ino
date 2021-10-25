
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

const int DATAOUT = 8;
const int DATAIN = 7;
const int LED = 5;

RH_ASK driver(2000, DATAIN, DATAOUT, 1);

void setup(){
  
  pinMode(DATAIN, INPUT);\
  pinMode(LED, OUTPUT);
  Serial.begin(9600);	// Debugging only
  while (!Serial);
  if (driver.init())
    Serial.println("init");
  else {
    Serial.printf("init failed\n");
  }
}

void loop()
{
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;
    Serial.print("Message Recieved: ");
    Serial.println((char*)buf);

    // Message with a good checksum received, dump it.
    driver.printBuffer("Got:", buf, buflen);
  }
}
