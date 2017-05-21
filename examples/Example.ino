#include "Ticker.h"

void printMessage();
void printCounter();
void printCountdown();
void blink();

bool ledState;

Ticker timer1(printMessage, 0, 1);
Ticker timer2(printCounter, 1000);
Ticker timer3(printCountdown, 1000, 5);
Ticker timer4;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(2000);
  timer4.setCallback(blink);
  timer4.setInterval(500);
  timer1.start();
  timer2.start();
  timer3.start();
  timer4.start();
  }

void loop() {
  timer1.update();
  timer2.update();
  timer3.update();
  timer4.update();
  }

void printCounter() {
  Serial.print("Counter ");
  Serial.println(timer2.getRepeatsCounter());
  }

  void printCountdown() {
    Serial.print("Countdowm ");
    Serial.println(timer3.getRepeats() - timer3.getRepeatsCounter());
    }

void printMessage() {
  Serial.println("Hello!");
  }

void blink() {
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;
  }
