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

#include "Ticker.h"

Ticker::Ticker() {
	init(NULL, 0, 0, MICROS);
	}

Ticker::Ticker(fptr callback, uint32_t interval, uint16_t repeats, resolution_t resolution) {
	init(callback, interval, repeats, resolution);
	}

Ticker::~Ticker() {}

void Ticker::init(fptr callback, uint32_t interval, uint16_t repeats, resolution_t resolution) {
	_resolution = resolution;
	setInterval(interval);
	setRepeats(repeats);
	setCallback(callback);
	enabled = false;
	lastTime = 0;
	counter = 0;
	}

void Ticker::start() {
	if (getCallback() == NULL) return;
	if(_resolution == MILLIS) lastTime = millis();
	else lastTime = micros();
	enabled = true;
	counter = 0;
	state = RUNNING;
	}

void Ticker::resume() {
	if (getCallback() == NULL) return;
	if(_resolution == MILLIS) lastTime = millis() - diffTime;
	else lastTime = micros() - diffTime;
	if(state == STOPPED) counter = 0;
	enabled = true;
	state = RUNNING;
	}

void Ticker::stop() {
	enabled = false;
	counter = 0;
	state = STOPPED;
	}

void Ticker::pause() {
	if(_resolution == MILLIS) diffTime = millis() - lastTime;
	else diffTime = micros() - lastTime;
	enabled = false;
	state = PAUSED;
	}

void Ticker::update() {
	if(tick()) call();
	}

bool Ticker::tick() {
	if(!enabled)	return false;
	if(_resolution == MILLIS) {
		if ((millis() - lastTime) >= _interval) {
			lastTime = millis();
			if(_repeats - counter == 1) {
				enabled = false;
				counter++;
				}
			else {
				counter++;
				}
	  	return true;
			}
		}
	else {
		if ((micros() - lastTime) >= _interval) {
			lastTime = micros();
			//if(countdown == 1)
			if(_repeats - counter == 1)
				{
				enabled = false;
				counter++;
				}
			else {
				counter++;
				}
			return true;
			}
		}
	return false;
	}

void Ticker::setInterval(uint32_t interval) {
	if(_resolution == MILLIS) _interval = interval;
	else _interval = interval * 1000;
	}

void Ticker::setCallback(fptr callback) {
	call = callback;
	}

void Ticker::setRepeats(uint16_t repeats) {
	_repeats = repeats;
	}

uint32_t Ticker::getElapsedTime() {
	//return millis() - lastTime;
	if(_resolution == MILLIS) return millis() - lastTime;
	else return micros() - lastTime;
	}

status_t Ticker::getState() {
	return state;
	}

uint32_t Ticker::getInterval() {
	return _interval;
	}

fptr Ticker::getCallback() {
	return call;
	}

uint16_t Ticker::getRepeats() {
	return _repeats;
	}

uint16_t Ticker::getRepeatsCounter() {
	return counter;
	}
