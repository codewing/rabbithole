//
// Created by codewing on 07.11.18.
//

#include "WormholeGame.hpp"
#include <glm/glm.hpp>
#include "MovementComponent.hpp"
#include "LevelGenerator.hpp"
#include "Rabbit.hpp"
#include <string>
#include "GameCameraController.hpp"
#include "../engine/core/GameMode.hpp"
#include "DeathmatchGameMode.hpp"


WormholeGame::WormholeGame(EngineCore &engine) :
                    GameModule(engine){}

void WormholeGame::update(float deltaTime) {
    gameMode->update(deltaTime);
}

void WormholeGame::initialize() {
    gameMode = std::make_unique<DeathmatchGameMode>();
    gameMode->initialize();
}
