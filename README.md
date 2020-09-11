# Arduino Ticker Library v3.1.x

The **Arduino Ticker Library** allows you to create easily Ticker callbacks, which can call a function in a predetermined interval. You can change the number of repeats of the callbacks, if repeats is 0 the ticker runs in endless mode. Works like a "thread", where a secondary function will run when necessary. The library use no interupts of the hardware timers and works with the **micros() / millis()** function. You are not (really) limited in the number of Tickers.

## New in v2.0
- You can determine the number of repeats, instead of modes.
- The internal resolution is now **micros()**, this works with intervals up to 70 minutes. For longer intervals you can change the resolution to **millis()**.
```
cpp Ticker tickerObject(callbackFunction, 1000, 0, MILLIS)
```
- unified data types and smaller improvments

## New in v2.1
- You can change the interval time to microseconds.
```
cpp Ticker tickerObject(callbackFunction, 100, 0, MICROS_MICROS) // interval is now 100us
```
- smaller improvments

## New in v3.0
- radical simplified API
- generally you have to declare all settings in the constructor
- deleted many set and get functions
- if you need former functionality please use the version 2.1

## New in v3.1
- added interval function

## Installation

1. "Download":https://github.com/sstaub/Ticker/archive/master.zip the Master branch from GitHub.
2. Unzip and modify the folder name to "Ticker"
3. Move the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).


## How to use

First, include the TimerObject to your project:

```cpp
#include "Ticker.h"
```

Now, you can create a new object in setup():

```cpp
Ticker tickerObject(callbackFunction, 1000); 
tickerObject.start(); //start the ticker.
```

In your loop(), add:

```cpp
tickerObject.update(); //it will check the Ticker and if necessary, it will run the callback function.
```


## IMPORTANT
If you use delay(), the Ticker will be ignored! You cannot use delay() command with the TimerObject. Instead of using delay, you can use the Ticker itself. For example, if you need that your loop run twice per second, just create a Ticker with 500 ms. It will have the same result that delay(500), but your code will be always state.

## Example

Complete example. Here we created five timers, you can run it and test the result in the Serial monitor and the on board LED.

```cpp
#include "Ticker.h"

void printMessage();
void printCounter();
void printCountdown();
void blink();
void printCountUS();

bool ledState;
int counterUS;

Ticker timer1(printMessage, 0, 1); // once, immediately 
Ticker timer2(printCounter, 1000, MILLIS); // internal resolution is milli seconds
Ticker timer3(printCountdown, 1000, 5); // 5 times, every second
Ticker timer4(blink, 500); // changing led every 500ms
Ticker timer5(printCountUS, 100, 0, MICROS_MICROS); // the interval time is 100us and the internal resolution is micro seconds


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
```

## Documentation

### States
STOPPED / RUNNING / PAUSED

### Constructors / Destructor

**Ticker(fptr callback, uint32_t timer, uint32_t repeats = 0, resolution_t resolution = MICROS)**<br>
Creates a Ticker object
- parameter callback for the function name you want to call
- parameter timer sets the interval time in ms or us when using MICROS_MICROS with the resolution parameter
- parameter repeats sets the number of repeats the callback should executed, 0 is endless
- parameter resolution sets the internal resolution of the Ticker, it can MICROS, MICROS_MICROS or MILLIS

**~Ticker()**<br>
Destructor for Ticker object
	
### Functions

**void start()**<br>
Start the Ticker. Will count the interval from the moment that you start it. If it is paused, it will restart the Ticker.

**void resume()**<br>
Resume the Ticker. If not started, it will start it. If paused, it will resume it. For example, in a Ticker of 5 seconds, if it was paused at 3 seconds, the resume continues at 3 seconds. Start will set passed time to 0 and restart until it get 5 seconds.

**void pause()**<br>
Pause the Ticker, so you can resume it.

**void stop()**<br>
Stop the Ticker.

**void update()**<br>
Must called in the loop(), it will check the Ticker, and if necessary, will run the callback

**void interval(uint32_t timer)**<br>
Changes the interval time of the Ticker.

**status_t state()**<br>
Returns the state of the Ticker.

**uint32_t elapsed()**<br>
Returns the time passed since the last tick, ms or us depending from the resolution.

**uint32_t counter()**<br>
Returns the number of executed callbacks.



