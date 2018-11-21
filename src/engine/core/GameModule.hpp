//
// Created by codewing on 21.11.18.
//


#pragma once

class EngineCore;

class GameModule {

public:
    explicit GameModule(EngineCore& engine);
    virtual ~GameModule();

    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;

protected:
    EngineCore& engine;
};


