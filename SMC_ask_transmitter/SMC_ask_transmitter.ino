

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

const int DATAOUT = 8;
const int DATAIN = 7;
const int LED = 13;

//RH_ASK(uint16_t speed = 2000, uint8_t rxPin = 11, uint8_t txPin = 12, uint8_t pttPin = 10, bool pttInverted = false);
RH_ASK driver(2000, DATAIN, DATAOUT, 1);

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  Serial.begin(9600);	  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  const char *msg = "Hello World!";

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  digitalWrite(LED, HIGH);
  Serial.printf("%c\n", *msg);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(500);
}
