# Arduino Ticker Library v2.1

The **Arduino Ticker Library** allows you to create easily Ticker callbacks, which can call a function in a predetermined interval. You can change the number of repeats of the the callbacks, if repeats is 0 the ticker runs in endless mode. Works like a "thread", where a secondary function will run when necessary. The library use no interupts of the hardware timers and works with the **micros() / millis()** function. You are not (really) limited in the number of Tickers.

## New in v2.0
- You can determine the number of repeats, instead of modes.
- The internal resolution is now **micros()**, this works with intervals up to 70 minutes. For longer intervals you can change the resolution to **millis()**. ``` Ticker tickerObject(callbackFunction, 1000, 0, MILLIS) ```
- unified data types and smaller improvments

## New in v2.1
- You can change the interval time to microseconds. ``` Ticker tickerObject(callbackFunction, 100, 0, MICROS_MICROS) // interval is now 100us```
- smaller improvments

## Installation

1. "Download":https://github.com/sstaub/Ticker/archive/master.zip the Master branch from GitHub.
2. Unzip and modify the folder name to "Ticker"
3. Move the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).


## How to use

First, include the TimerObject to your project:

```
#include "Ticker.h"
```

Now, you can create a new object in setup():

```
Ticker tickerObject; 
tickerObject.setInterval(1000);
tickerObject.setCallback(callbackFunction);
tickerObject.start(); //start the ticker.
```

In your loop(), add:

```
tickerObject.update(); //it will check the Ticker 
and if necessary, it will run the callback function.
```


## IMPORTANT
If you use delay(), the Ticker will be ignored! You cannot use delay() command with the TimerObject. Instead of using delay, you can use the Ticker itself. For example, if you need that your loop run twice per second, just create a Ticker with 500 ms. It will have the same result that delay(500), but your code will be always state.

## Example

Complete example. Here we created three timers, you can run it and test the result in the Serial monitor and the on board LED.

```
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
```

## Documentation

### States
STOPPED / RUNNING / PAUSED

### Constructors / Destructor
**Ticker()**<br>
Creates a Ticker object without parameters.

**Ticker(fptr callback, uint32_t interval, uint16_t repeats = 0, resolution_t resolution = MICROS)**<br>
Creates a Ticker object
- parameter callback for the function name you want to call
- parameter interval sets the interval time in ms
- parameter interval resolution can changed to us instead of ms with setting the parameter resolution to MICROS_MICROS
- parameter repeats sets the number of repeats the callback should executed, 0 is endless
- parameter resolution sets the internal resolution of the Ticker, it can MICROS, MILLIS or MICROS_MICROS (for us intervals)

**~Ticker()**<br>
Destructor for Ticker object
	
### Functions

**void start()**<br>
Start the Ticker. Will count the interval from the moment that you start it. If it is paused, it will restart the Ticker.

**void resume()**<br>
Resume the Ticker. If not started, it will start it. If paused, it will resume it. For example, in a Ticker of 5 seconds, if it was paused in 3 seconds, the resume in continue in 3 seconds. Start will set passed time to 0 and restart until get 5 seconds.

**void pause()**<br>
Pause the Ticker, so you can resume it.

**void stop()**<br>
Stop the Ticker.

**void update()**<br>
Must to be called in the loop(), it will check the Ticker, and if necessary, will run the callback

**void setInterval(uint32_t interval)**<br>
Set callback interval in ms or us when using MICROS_MICROS.

**void setCallback(ftpr callback)**<br>
Set function callback.

**void setRepeats(uint16_t repeats)**<br>
Set the number of the repeats, 0 (standard) is endless mode.

**status_t getState()**<br>
Returns the state of the Ticker.

**uint32_t getElapsedTime()**<br>
Returns the time passed since the last tick.

**uint32_t getInterval()**<br>
Get the interval of the Ticker.

**fptr getCallback()**<br>
Get the callback of the Ticker.

**uint16_t getRepeats()**<br>
Get the number of the repeats.

**uint16_t getRepeatsCounter()**<br>
Get the number of executed callbacks.



