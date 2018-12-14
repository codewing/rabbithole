//
// Created by codewing on 14/12/2018.
//

#pragma once

#include <memory>

#include "GameCameraController.hpp"
#include "../engine/core/GameMode.hpp"

class GameObject;
class Rabbit;
class RabbitPhysicsComponent;
class DeathmatchUIComponent;

class DeathmatchGameMode : public GameMode {

public:
    DeathmatchGameMode() = default;

    void initialize() override;
    void update(float deltaTime) override;

    void gameObjectDied(RabbitPhysicsComponent* rabbitPhysicsComponent);

private:
    std::shared_ptr<GameObject> level = nullptr;
    std::shared_ptr<GameObject> waterGO = nullptr;
    std::shared_ptr<GameObject> hudElements = nullptr;
    std::shared_ptr<DeathmatchUIComponent> uiComponent = nullptr;

    GameCameraController cameraController;
    std::unique_ptr<Rabbit> redRabbit;
    std::unique_ptr<Rabbit> blueRabbit;

    int scoreRed = 0;
    int scoreBlue = 0;

    bool isPlaying = false;

    void spawnLevel();
    void spawnWater();
    void spawnRabbits();
    void initializeInterface();
};
