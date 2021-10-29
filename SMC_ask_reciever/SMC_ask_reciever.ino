/*
   Project: smart room controller
   Description: RF smart room controller main hub
   Author: Ben Klein
   Date: 25-OCT-2021
*/
#include <SPI.h>
#include <Wire.h>
#include <Encoder.h>
#include <Ethernet.h>
#include <VirtualWire.h>
#include <Adafruit_NeoPixel.h>
#include <mac.h>
#include <hue.h>
#include <wemo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SEALEVELPRESSURE_HPA (1013.25)
#define SCREEN_ADDRESS 0x3C

const int transmit_en_pin = 1;
const int transmit_pin = 2;
const int HSLSW = 3;
const int ENCSW = 4;
const int WSCSW = 5;
const int WPWSW = 6;
const int COLSW = 7;
const int receive_pin = 8;
const int ENCA = 14;
const int ENCB = 15;
const int LED = 16;
const int EMOSW = 20;
const int DELAY = 250;




int i; //hue select
int c; //hue color
int w; //wemoselect
int position;
int lastPos;
int briPos;
int WEMO[5];
int RAINBOW[] = {HueRed, HueOrange, HueYellow, HueGreen, HueBlue, HueIndigo, HueViolet};

bool buttonPress1;
bool buttonState1;
bool buttonPress2;
bool buttonState2;
bool buttonPress3;
bool buttonState3;
bool buttonPress4;
bool buttonState4;
bool buttonPress5;
bool buttonState5;
bool buttonPress6;
bool buttonState6;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

Encoder myEnc(ENCA, ENCB);

void setup() {
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  delay(1000);
  Serial.begin(9600);	// Debugging only
  while (!Serial);
  Serial.printf("setup");

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();

  pinMode(LED, OUTPUT);
  buttonPress1 = true;
  buttonState1 = false;
  buttonPress2 = true;
  buttonState2 = false;
  buttonPress3 = true;
  buttonState3 = false;
  buttonPress4 = true;
  buttonState4 = false;
  buttonPress5 = true;
  buttonState5 = false;
  buttonPress6 = true;
  buttonState6 = false;
  pinMode(ENCSW, INPUT_PULLUP);
  pinMode(COLSW, INPUT_PULLUP);
  pinMode(WPWSW, INPUT_PULLUP);
  pinMode(WSCSW, INPUT_PULLUP);
  pinMode(HSLSW, INPUT_PULLUP);
  pinMode(EMOSW, INPUT_PULLUP);

  c = 0;
  w = 0;
  i = 0;

  position = 0;
  lastPos = 0;
  myEnc.write(48);

  Ethernet.begin(mac);
  delay(200);          //ensure Serial Monitor is up and running
  //  printIP();
  //  Serial.printf("LinkStatus: %i  \n", Ethernet.linkStatus());
}

void loop() {
  buttonPress1 = digitalRead(ENCSW);
  button1();
  buttonPress2 = digitalRead(COLSW);
  button2();
  buttonPress3 = digitalRead(WPWSW);
  button3();
  buttonPress4 = digitalRead(WSCSW);
  button4();
  buttonPress5 = digitalRead(HSLSW);
  button5();
  buttonPress6 = digitalRead(EMOSW);
  button6();
  encoderPos();
  checkMessage();
}


void input1(int bufVal) {
  if (bufVal == 0x31) {
    hueLamp();
    buttonState1 = !buttonState1;
    Serial.printf("Hue Lights On/Off\n");
    delay(DELAY);
  }
  if (bufVal == 0x32) {
    c++;
    allStatus();
    if (c > 6) {
      c = 0;
      allStatus();
    }
    Serial.printf("Hue Color Select. ButtonState2 = %i, i=%i\n", buttonState2,  c);
  }
  if (bufVal == 0x33) {
    buttonState3 = !buttonState3;
    if (buttonState3 == true) {
      switchON(w);
      allStatus();
    }
    else {
      switchOFF(w);
      allStatus();
    }
    Serial.printf("WemoPower\n");
  }
  if (bufVal == 0x34) {
    w++;
    allStatus();
    if (w > 4) {
      w = 0;
      allStatus();
    }
    Serial.printf("Wemo%i\n", w);
  }
  if (bufVal == 0x35) {
    i++;
    allStatus();
    if (i > 6) {
      i = 0;
      allStatus();
    }
    Serial.printf("Hue Light%i selected\n", i);
  }
}
void checkMessage() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    digitalWrite(LED, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    //    Serial.print("Got: ");

    Serial.printf("%x", buf[0]);
    digitalWrite(LED, LOW);
    input1(buf[0]);
  }
}


void button1() {
  if (buttonPress1 == false) {
    hueLamp();
    buttonState1 = !buttonState1;
    Serial.printf(" %i power on/off \n",  buttonState1);
    delay(DELAY);
  }
  click1();
}

void click1() {
  if (buttonState1 == true) {
  }
}

void button2() {
  if (buttonPress2 == false) {
    c++;
    allStatus();
    buttonState2 = !buttonState2;
    Serial.printf("%i Red %i\n", buttonState2, c);
    delay(DELAY);
    if (c > 6) {
      c = 0;
      allStatus();
    }
  }
  click2();
}

void click2() {
  if (buttonState2 == true) {
  }
}

void button3() {
  if (buttonPress3 == false) {
    buttonState3 = !buttonState3;
    wemoPower();
    Serial.printf(" WemoPower %i\n",  buttonState3);
    delay(DELAY);
  }
  click3();
}

void click3() {
  if (buttonState3 == true) {
  }
}

void button4() {
  if (buttonPress4 == false) {
    w++;
    allStatus();
    buttonState4 = !buttonState4;
    Serial.printf("Wemo Select %i\n", w);
    delay(DELAY);
    if (w > 4) {
      w = 0;
      allStatus();
    }
  }
  click4();
}

void click4() {
  if (buttonState4 == true) {
  }
}

void button5() {
  if (buttonPress5 == false) {
    i++;
    allStatus();
    buttonState5 = !buttonState5;
    Serial.printf("%i Hue Select %i\n", buttonState5, i);
    delay(DELAY);
    if (i > 6) {
      i = 1;
      allStatus();
    }
  }
  click5();
}

void click5() {
  if (buttonState5 == true) {
  }
}

void button6() {
  if (buttonPress6 == false) {
    buttonState6 = !buttonState6;
    delay(5000);
    Serial.printf("CALM DOWN %i\n", buttonState6);
    calmDown();
    calmDownStatus();
  }
  click6();
}

void click6() {
  if (buttonState6 == true) {
  }
}


void encoderPos() {  //encoder position and mapping
  position = myEnc.read();
  if (position < 0) {
    position = 0;
  }
  if (position > 96) {
    position = 96;
  }
  briPos = map(position, 0, 96, 0, 255);
  if (position != lastPos) {
    Serial.printf("%i, %i\n", position, briPos);
    lastPos = position;
  }
  //    hueLamp();
}

void hueLamp() {
  setHue(i, buttonState1, RAINBOW[c], briPos, 255);
  if (buttonState1 == false) {
    allStatus();
  }
  else {
    allStatus();
  }
}

void calmDown() {
  for (i = 1; i < 6; i++) {
    setHue(i, buttonState6, HueBlue, 255, 255);
    if (buttonState1 == false) {
      calmDownStatus();
    }
    else {
    }
  }
}


void wemoPower() {
  if (buttonState3 == true) {
    switchON(w);
    allStatus();
  }
  else {
    switchOFF(w);
    allStatus();
  }

}

void allStatus() {
  Serial.printf(" Hue %i selected\n Hue color %i selected\n Hue %i %i\n Wemo %i selected\n Wemo %i %i\n", i, c, i, buttonState1, w, w, buttonState3);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setRotation(0);
  display.printf(" Hue %i selected\n Hue color %i selected\n Hue %i %i\n Wemo %i selected\n Wemo %i %i\n", i, c, i, buttonState1, w, w, buttonState3);
  display.display();
}

void calmDownStatus() {
  Serial.printf("CALM\n DOWN\n");
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setRotation(0);
  display.printf("CALM\n DOWN\n");
  display.display();
}
