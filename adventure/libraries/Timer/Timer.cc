#include <Arduino.h>
#include "Constants.h"
#include "Timer.h"

Timer::Timer(unsigned long delay) : _delay(delay) {}

void Timer::startTimer() {
    _start = millis();
}

bool Timer::timeIsUp() const {
    return millis() >= _start + _delay;
}

void Timer::speedUp() {
    _delay /= SPEED_BOOTS_MULTIPLIER;
}

void Timer::slowDown() {
    _delay *= SPEED_BOOTS_MULTIPLIER;
}