//
// Created by codewing on 14/12/2018.
//

#include "DeathmatchGameMode.hpp"

#include "Rabbit.hpp"
#include "LevelGenerator.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include <sre/Sprite.hpp>

void DeathmatchGameMode::initialize() {
    spawnLevel();
    spawnWater();
    initializeInterface();
    spawnRabbits();
}

void DeathmatchGameMode::update(float deltaTime) {
    cameraController.update(deltaTime);

    auto middle = (redRabbit->getPosition() + blueRabbit->getPosition()) / 2.0f;
    auto distance = glm::length(redRabbit->getPosition() - blueRabbit->getPosition());
    cameraController.focusOn(middle, distance, 0.0f);
}

void DeathmatchGameMode::spawnWater() {
    water = ObjectManager::GetInstance()->CreateGameObject("Water");
    water->setLocalPosition({0, 0});

    auto waterSprite = ObjectManager::GetInstance()->GetTextureSystem().getSpriteFromAtlas("water.png", "environment");
    auto waterSpriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(water.get());
    waterSpriteComp->setSprite(waterSprite);
}

void DeathmatchGameMode::spawnLevel() {
    LevelGenerator level({2048,2048}, 0.3);
    std::shared_ptr<GameObject> world = level.generateLevel();
}

void DeathmatchGameMode::initializeInterface() {
    cameraController.initialize();
    cameraController.focusOn({500, 500}, 1400, 0);
}

void DeathmatchGameMode::spawnRabbits() {
    redRabbit = std::make_unique<Rabbit>("red", glm::vec2{500, 780}, 0);
    blueRabbit = std::make_unique<Rabbit>("blue", glm::vec2{1500, 750}, -1);
}
