//
// Created by codewing on 14/12/2018.
//

#pragma once

#include <memory>

#include "GameCameraController.hpp"
#include "../engine/core/GameMode.hpp"

class GameObject;
class Rabbit;

class DeathmatchGameMode : public GameMode {

public:
    DeathmatchGameMode() = default;

    void initialize() override;
    void update(float deltaTime) override;

private:

    int waterHeight = 200;

    std::shared_ptr<GameObject> level = nullptr;
    std::shared_ptr<GameObject> water = nullptr;
    std::shared_ptr<GameObject> hudElements = nullptr;

    GameCameraController cameraController;
    std::unique_ptr<Rabbit> redRabbit;
    std::unique_ptr<Rabbit> blueRabbit;

    void spawnLevel();
    void spawnWater();
    void spawnRabbits();
    void initializeInterface();
};
