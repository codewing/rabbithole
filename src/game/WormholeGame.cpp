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
                    redRabbit {engine, "red", {600, 1000}},
                    blueRabbit {engine, "blue", {700, 1100}} {}

void WormholeGame::update(float deltaTime) {
    cameraController.update(deltaTime);

    if(cameraController.isAtTarget) {
        cameraController.focusOn(redRabbit.getPosition(), 700, 0.f);
    }
}

void WormholeGame::initialize() {
    LevelGenerator level(engine, {2048,2048}, 0.6);
    level.generateLevel();

    cameraController.initialize();
    cameraController.focusOn({500, 500}, 1400, 0);
}
