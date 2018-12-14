//
// Created by codewing on 07.11.18.
//

#pragma once

#include "../engine/core/EngineCore.hpp"
#include "../engine/core/GameModule.hpp"
#include "../engine/core/GameMode.hpp"
#include <memory>

class WormholeGame : public GameModule {
public:
    WormholeGame(EngineCore &engine);

private:

    std::unique_ptr<GameMode> gameMode;

    void initialize() override;
    void update(float deltaTime);
};
