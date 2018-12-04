//
// Created by codewing on 07.11.18.
//

#pragma once

#include "../engine/core/EngineCore.hpp"
#include "../engine/core/GameModule.hpp"
#include <memory>

class WormholeGame : public GameModule {
public:
    WormholeGame(EngineCore &engine);

private:

    void initialize() override;
    void update(float deltaTime);
};
