/* Ticker library code is placed under the MIT license
 * Copyright (c) 2017 Stefan Staub
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TICKER_H
#define TICKER_H

#include "Arduino.h"

/** Ticker internal resolution
 *
 * @param MICROS default, the resoöution is in micro seconds, max is 70 minutes, the real resoltuion is 4 microseconds at 16MHz CPU cycle
 * @param MILLIS set the resolution to millis, for longer cycles over 70 minutes
 *
 */
enum resolution_t {MICROS, MILLIS};

/** Ticker status
 *
 * @param STOPPED default, ticker is stopped
 * @param RUNNIBG ticker is running
 * @param PAUSED ticker is paused
 *
 */
enum status_t {STOPPED, RUNNING, PAUSED};

typedef void (*fptr)();

class Ticker {

public:

	/** create a Ticker object with none parameter which can set later
	 *
	 */
	Ticker();

	/** create a Ticker object
	 *
	 * @param callback the name of the function to call
	 * @param ms interval length
	 * @param repeats default 0 -> endless, repeats > 0 -> number of repeats
	 * @param resolution default MICROS for tickers under 70min, use MILLIS for tickers over 70 min
	 *
	 */
	Ticker(fptr callback, uint32_t ms, uint16_t repeats = 0, resolution_t resolution = MICROS);

	/** destructor for the Ticker object
	 *
	 */
	~Ticker();

	/** start the ticker
	 *
	 */
	void start();

	/** resume the ticker. If not started, it will start it.
	 *
	 */
	void resume();

	/** pause the ticker
	 *
	 */
	void pause();

	/** stops the ticker
	 *
	 */
	void stop();

	/** must to be called in the main loop(), it will check the Ticker, and if necessary, will run the callback
	 *
	 */
	void update();

	/** interval time setting
	 *
	 * @param interval sets the interval time in ms
	 *
	 */
	void setInterval(uint32_t interval);

	/** callback setting
	 *
	 * @param callback sets the name of the function to call
	 *
	 */
	void setCallback(fptr callback);

	/** number of repeats
	 *
	 * @param repeats sets the number of repeats, 0 is endless mode
	 *
	 */
	void setRepeats(uint16_t repeats);

	/** actual ellapsed time
	 *
	 * @returns the elapsed time after the last tick
	 *
	 */
	uint32_t getElapsedTime();

	/** get the state of the ticker
	 *
	 * @returns the state of the ticker: STOPPED, RUNNING or PAUSED
	 */
	status_t getState();

	/** get the interval time
	 *
	 * @returns the interval time of the ticker object
	 *
	 */
	uint32_t getInterval();

	/** get the callback pointer
	 *
	 * @returns the function pointer of the callback
	 *
	 */
	fptr getCallback();

	/** get the numbers of repeats
	 *
	 * @returns the number of repeats, 0 is endless mode
	 *
	 */
	uint16_t getRepeats();

	/** get the numbers of executed repeats
	 *
	 * @returns the number of executed repeats
	 *
	 */
	uint16_t getRepeatsCounter();


private:
	void init(fptr callback, uint32_t interval, uint16_t repeats, resolution_t resolution);
	bool tick();
	bool enabled;
	uint32_t _interval;
	uint16_t _repeats;
	resolution_t _resolution = MICROS;
	uint32_t counter;
	status_t state;
	fptr call;
	uint32_t lastTime;
	uint32_t diffTime;
};

#endif // TICKER_H
