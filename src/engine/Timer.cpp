//
// Created by codewing on 08.11.18.
//

#include "Timer.hpp"

Timer::Timer() :  startPoint(Clock::now()),
                lastTick(Clock::now()),
                lastDelta(0) {}

void Timer::start() {
    startPoint = Clock::now();
    lastTick = Clock::now();
    lastDelta = 0.0f;
}

void Timer::tick() {
    auto tick = Clock::now();
    lastDelta = std::chrono::duration_cast<MilliSeconds>(tick - lastTick).count();
    lastTick = tick;
}

float Timer::getDeltaTime() {
    return lastDelta;
}
