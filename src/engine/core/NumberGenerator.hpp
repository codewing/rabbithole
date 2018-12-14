//
// Created by codewing on 14.12.18.
//

#pragma once

#include <random>


class NumberGenerator {

public:
    NumberGenerator(float min, float max) : rd{}, mt{rd()}, dist{min, max} {}

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_real_distribution<double>  dist;

    double rnd() {
        return dist(mt);
    }
};

