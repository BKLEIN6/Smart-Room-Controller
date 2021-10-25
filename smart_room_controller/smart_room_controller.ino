/*
   Project: smart room controller
   Description: RF smart room controller 
   Author: Ben Klein
   Date: 25-OCT-2021
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Encoder.h>
#include <mac.h>
#include <hue.h>

const int LED = 2;
const int BLINK = 3;
const int DELAY = 250;
const int ENCSW = 21;
const int YELSW = 16;
const int ENCA = 14;
const int ENCB = 15;
const int LAMP = 3;

bool buttonPress1;
bool buttonState1;
bool buttonPress2;
bool buttonState2;


int i;
int position;
int lastPos;
int briPos;
int RAINBOW[] = {HueRed, HueOrange, HueYellow, HueGreen, HueBlue, HueIndigo, HueViolet};

Encoder myEnc(ENCA, ENCB);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(LED, OUTPUT);
  buttonPress1 = true;
  buttonState1 = false;
  buttonPress2 = true;
  buttonState2 = false;
  pinMode(ENCSW, INPUT_PULLUP);
  pinMode(YELSW, INPUT_PULLUP);
  i = 0;
  myEnc.write(48);

  Ethernet.begin(mac);
  delay(200);          //ensure Serial Monitor is up and running
  //  printIP();
  //  Serial.printf("LinkStatus: %i  \n", Ethernet.linkStatus());

}

void loop() {
  buttonPress1 = digitalRead(ENCSW);
  button1();
  buttonPress2 = digitalRead(YELSW);
  button2();
  encoder();
}

void blinkLED() {
  for (i = 0; i < BLINK; i++) {
    delay(DELAY);
    digitalWrite(LED, HIGH);
    delay(DELAY);
    digitalWrite(LED, LOW);
    //    Serial.printf("%i\n", i);
  }
}


void button1() {
  if (buttonPress1 == false) {
    buttonState1 = !buttonState1;
    Serial.printf("%i blinks %i ENC\n", BLINK, buttonState1);
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
    i++;
    buttonState2 = !buttonState2;
    Serial.printf("%i Red %i\n", buttonState2, i);
    delay(DELAY);
    if (i > 6) {
      i = 0;
    }
  }
  click2();
}

void click2() {
  if (buttonState2 == true) {
  }
}


void encoder() {  //encoder position and mapping
  position = myEnc.read();
  if (buttonState1 == true) {
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
    hueLamp();
  }
}

void hueLamp() {
  setHue(LAMP, buttonState1, RAINBOW[i], briPos, 255);
}
