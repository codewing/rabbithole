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


WormholeGame::WormholeGame(EngineCore &engine) : GameModule(engine) {}

void WormholeGame::update(float deltaTime) {
    cameraController.update(deltaTime);

    if(cameraController.isAtTarget) {
        cameraController.focusOn({1024, 0}, 700, 0.5f);
    }
}

void WormholeGame::initialize() {

    Rabbit redRabbit {engine, "red", {200, 600}};
    Rabbit blueRabbit {engine, "blue", {300, 700}};

    LevelGenerator level({2048,2048}, 0.6);
    level.generateLevel();

    cameraController.initialize();
    cameraController.focusOn({1024, 1024}, 700, 0);
}
