//
// Created by codewing on 08.11.18.
//

#pragma once

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<float, std::chrono::seconds::period>;

class Timer {
public:
    Timer();

    void start();
    void tick();

    float getDeltaTime();

private:

    std::chrono::time_point<Clock> startPoint;
    std::chrono::time_point<Clock> lastTick;

    float lastDelta = 0;
};
