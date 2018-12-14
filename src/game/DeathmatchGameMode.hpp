//
// Created by codewing on 14/12/2018.
//

#pragma once

#include <memory>
#include <vector>
#include <random>

#include "GameCameraController.hpp"
#include "../engine/core/GameMode.hpp"
#include "../engine/core/NumberGenerator.hpp"

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

    std::vector<glm::vec2> spawnPositions;

    int scoreRed = 0;
    int scoreBlue = 0;
    int maxScore = 15;

    bool isPlaying = false;
    std::vector<RabbitPhysicsComponent*> playersToRespawn;

    std::unique_ptr<NumberGenerator> rng;

private:

    void spawnLevel();
    void spawnWater();
    void spawnRabbits();
    void initializeInterface();
};
