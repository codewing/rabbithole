//
// Created by codewing on 08.11.18.
//

#include "Timer.hpp"

Timer::Timer() :  startPoint(Clock::now()),
                lastTick(Clock::now())
                {}

void Timer::start() {
    startPoint = Clock::now();
    lastTick = Clock::now();
    lastDelta = 0.0f;
}

void Timer::tick() {
    auto tick = Clock::now();
    Seconds dur = tick - lastTick;
    lastDelta = dur.count();
    lastTick = tick;
}

float Timer::getDeltaTime() {
    return lastDelta;
}
