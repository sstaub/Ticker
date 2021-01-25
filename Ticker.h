/* Ticker library code is placed under the MIT license
 * Copyright (c) 2018 Stefan Staub
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
enum resolution_t {
	MICROS,
	MILLIS,
	MICROS_MICROS
	};

/** Ticker status
 *
 * @param STOPPED default, ticker is stopped
 * @param RUNNIBG ticker is running
 * @param PAUSED ticker is paused
 *
 */
enum status_t {
	STOPPED,
	RUNNING,
	PAUSED};

#if defined(__arm__) || defined(ESP8266) || defined(ESP32)
#include <functional>
using fptr = std::function<void()>;
#else
typedef void (*fptr)();
#endif


class Ticker {

public:

	/** create a Ticker object
	 *
	 * @param callback the name of the function to call
	 * @param timer interval length in ms or us
	 * @param repeat default 0 -> endless, repeat > 0 -> number of repeats
	 * @param resolution default MICROS for tickers under 70min, use MILLIS for tickers over 70 min
	 *
	 */
	Ticker(fptr callback, uint32_t timer, uint32_t repeat = 0, resolution_t resolution = MICROS);

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

	/**
	 * @brief set the interval timer
	 * 
	 * @param timer interval length in ms or us
	 */
	void interval(uint32_t timer);

	/**
	 * @brief get the interval time
	 * 
	 * @returns the interval time
	 */
	uint32_t interval();

	/** actual ellapsed time
	 *
	 * @returns the elapsed time after the last tick
	 *
	 */
	uint32_t elapsed();

	/** time remaining to the next tick
	 *
	 * @returns the remaining time to the next tick in ms or us depending from mode
	 *
	 */
	uint32_t remaining();

	/** get the state of the ticker
	 *
	 * @returns the state of the ticker: STOPPED, RUNNING or PAUSED
	 */
	status_t state();

	/** get the numbers of executed repeats
	 *
	 * @returns the number of executed repeats
	 *
	 */
	uint32_t counter();

private:
	bool tick();
	bool enabled;
	uint32_t timer;
	uint32_t repeat;
	resolution_t resolution = MICROS;
	uint32_t counts;
	status_t status;
	fptr callback;
	uint32_t lastTime;
	uint32_t diffTime;
};

#endif
