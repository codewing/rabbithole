//
// Created by codewing on 07.11.18.
//

#pragma once

#include "../engine/core/EngineCore.hpp"
#include "../engine/core/GameModule.hpp"
#include <memory>

#include "GameCameraController.hpp"

class WormholeGame : public GameModule {
public:
    WormholeGame(EngineCore &engine);

private:

    GameCameraController cameraController;

    void initialize() override;
    void update(float deltaTime);
};
