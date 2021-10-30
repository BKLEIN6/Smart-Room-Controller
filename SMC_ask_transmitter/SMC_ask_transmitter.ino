/*
   Project: smart room controller Transmitter
   Description: RF smart room controller main hub
   Author: Ben Klein
   Date: 25-OCT-2021
*/
#include <VirtualWire.h>

const int led_pin = 8;
const int transmit_pin = 7;
const int receive_pin = 9;
const int transmit_en_pin = 1;
const int HPWSW = 6;
const int HCSSW = 5;
const int WEPSW = 4;
const int WESSW = 3;
const int HLSSW = 2;
const int DELAY = 250;

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

void setup() {

  Serial.begin(9600);
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec

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
  
  pinMode(HPWSW, INPUT_PULLUP);
  pinMode(HCSSW, INPUT_PULLUP);
  pinMode(WEPSW, INPUT_PULLUP);
  pinMode(WESSW, INPUT_PULLUP);
  pinMode(HLSSW, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
}

byte count = 1;

void loop() {
  buttonPress1 = digitalRead(HPWSW);
  button1();
  buttonPress2 = digitalRead(HCSSW);
  button2();
  buttonPress3 = digitalRead(WEPSW);
  button3();
  buttonPress4 = digitalRead(WESSW);
  button4();
  buttonPress5 = digitalRead(HLSSW);
  button5();
}

void msg1() {
  char msg[1] = {'1'};
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  Serial.printf("Message 1 Sent\n");
  delay(1000);
}

void msg2() {
  char msg[2] = {'2'};
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  Serial.printf("Message 2 Sent\n");
  delay(1000);
}

void msg3() {
  char msg[1] = {'3'};
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 2);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  Serial.printf("Message 3 Sent\n");
  delay(1000);
}

void msg4() {
  char msg[1] = {'4'};
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  Serial.printf("Message 4 Sent\n");
  delay(1000);
}


void msg5() {
  char msg[1] = {'5'};
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  Serial.printf("Message 5 Sent\n");
  delay(1000);
}

void button1() {
  if (buttonPress1 == false) {
    msg1();
    buttonState1 = !buttonState1;
    Serial.printf("buttonState1 is now: %i\n", buttonState1);
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
    msg2();
    buttonState2 = !buttonState2;
    Serial.printf("buttonState2 is now: %i\n", buttonState2);
    delay(DELAY);
  }
  click2();
}

void click2() {
  if (buttonState2 == true) {
  }
}

void button3() {
  if (buttonPress3 == false) {
    msg3();
    buttonState3 = !buttonState3;
    Serial.printf("buttonState3 is now: %i\n", buttonState3);
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
    msg4();
    buttonState4 = !buttonState4;
    Serial.printf("buttonState4 is now: %i\n", buttonState4);
    delay(DELAY);
  }
  click4();
}

void click4() {
  if (buttonState4 == true) {
  }
}

void button5() {
  if (buttonPress5 == false) {
    msg5();
    buttonState5 = !buttonState5;
    Serial.printf("buttonState5 is now: %i\n", buttonState5);
    delay(DELAY);
  }
  click5();
}

void click5() {
  if (buttonState5 == true) {
  }
}
