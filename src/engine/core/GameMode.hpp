//
// Created by codewing on 14/12/2018.
//

#pragma once

class GameMode {

public:
    virtual ~GameMode() = default;

    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;
};
