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


WormholeGame::WormholeGame(EngineCore &engine) :
                    GameModule(engine),
                    redRabbit {engine, "red", {600, 1000}, 0},
                    blueRabbit {engine, "blue", {700, 1100}, -1} {}

void WormholeGame::update(float deltaTime) {
    cameraController.update(deltaTime);

    if(cameraController.isAtTarget) {
        auto middle = (redRabbit.getPosition() + blueRabbit.getPosition()) / 2.0f;
        auto distance = glm::length(redRabbit.getPosition() - blueRabbit.getPosition());
        cameraController.focusOn(middle, distance, 0.0f);
    }
}

void WormholeGame::initialize() {
    LevelGenerator level(engine, {2048,2048}, 0.6);
    level.generateLevel();

    cameraController.initialize();
    cameraController.focusOn({500, 500}, 1400, 0);
}
