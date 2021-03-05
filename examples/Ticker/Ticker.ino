#include "Ticker.h"

void printMessage();
void printCounter();
void printCountdown();
void blink();
void printCountUS();

bool ledState;
int counterUS;

Ticker timer1(printMessage, 0, 1);
Ticker timer2(printCounter, 1000, 0, MILLIS);
Ticker timer3(printCountdown, 1000, 5);
Ticker timer4(blink, 500);
Ticker timer5(printCountUS, 100, 0, MICROS_MICROS);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(2000);
  timer1.start();
  timer2.start();
  timer3.start();
  timer4.start();
  timer5.start();
  }

void loop() {
  timer1.update();
  timer2.update();
  timer3.update();
  timer4.update();
  timer5.update();
  if (timer4.counter() == 20) timer4.interval(200);
  if (timer4.counter() == 80) timer4.interval(1000);
  }

void printCounter() {
  Serial.print("Counter ");
  Serial.println(timer2.counter());
  }

void printCountdown() {
  Serial.print("Countdowm ");
  Serial.println(5 - timer3.counter());
  }

void printMessage() {
  Serial.println("Hello!");
  }

void blink() {
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;
  }

void printCountUS() {
  counterUS++;  
  if (counterUS == 10000) {
    Serial.println("10000 * 100us");
    counterUS = 0;
    }
  }
