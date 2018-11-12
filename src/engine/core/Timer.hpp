//
// Created by codewing on 08.11.18.
//

#pragma once

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
using MilliSeconds = std::chrono::duration<float, std::chrono::milliseconds::period>;

class Timer {
public:
    Timer();

    void start();
    void tick();

    float getDeltaTime();

private:

    std::chrono::time_point<Clock, MilliSeconds> startPoint;
    std::chrono::time_point<Clock, MilliSeconds> lastTick;

    float lastDelta;
};
