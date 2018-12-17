//
// Created by codewing on 14/12/2018.
//

#include "DeathmatchGameMode.hpp"

#include "player/Rabbit.hpp"
#include "terrain/LevelGenerator.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include "player/RabbitPhysicsComponent.hpp"
#include "ResetPhysicsComponent.hpp"
#include "DeathmatchUIComponent.hpp"
#include "../engine/debug/Log.hpp"
#include <sre/Sprite.hpp>
#include "player/HealthComponent.hpp"

/*
	class managing the deathMatch mode, meaning two rabbits, blue and red respectively.
	- creating the level
	- creating the rabbits
	- managing points of rabbits deaths
	- respawning rabbits when dead
	- creating interface for points
	- calculating values for intelligent camera
*/

void DeathmatchGameMode::initialize() {
    scoreRed = scoreBlue = 0;
    spawnLevel();
    spawnWater();
    initializeInterface();
    spawnRabbits();
    isPlaying = true;
}

void DeathmatchGameMode::update(float deltaTime) {
    cameraController.update(deltaTime);

    auto middle = (redRabbit->getPosition() + blueRabbit->getPosition()) / 2.0f;
    auto distance = glm::length(redRabbit->getPosition() - blueRabbit->getPosition());
    cameraController.focusOn(middle, distance, 0.0f);

    if(redRabbit->getHealthValue() <= 0.0f) gameObjectDied(redRabbit->getRabbitPhysicsComponent());
    if(blueRabbit->getHealthValue() <= 0.0f) gameObjectDied(blueRabbit->getRabbitPhysicsComponent());

    uiComponent->updateScore(scoreRed, scoreBlue);

    if(!playersToRespawn.empty()) {
        for(auto player : playersToRespawn) {
            int spawnNumber = static_cast<int>(rng->rnd());
            auto spawnLocation = spawnPositions[spawnNumber];
            player->teleport(spawnLocation, 0);
            player->setLinearVelocity({0, 0});
            player->getGameObject()->getComponent<HealthComponent>()->setHealthValue(100);
        }
        playersToRespawn.clear();
    }
}

void DeathmatchGameMode::spawnWater() {
    waterGO = ObjectManager::GetInstance()->CreateGameObject("Water");
    waterGO->setLocalPosition({1024, 85});

    auto waterSprite = ObjectManager::GetInstance()->GetTextureSystem().getSpriteFromAtlas("water.png", "environment");
    waterSprite.setOrderInBatch(16959);
    auto waterSpriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(waterGO.get());
    waterSpriteComp->setSprite(waterSprite);

    auto resetComponent = ObjectManager::GetInstance()->CreateComponent<ResetPhysicsComponent>(waterGO.get());
    resetComponent->initBox(b2_staticBody, {999999999, 20}, {0, 0}, 1.0f);
    resetComponent->setSensor(true);
    resetComponent->setGameMode(this);
}

void DeathmatchGameMode::spawnLevel() {
    LevelGenerator level({2048,2048}, 0.3);
    std::shared_ptr<GameObject> world = level.generateLevel();
    spawnPositions = {level.getSpawnPoints()};
    rng = std::make_unique<NumberGenerator>(0, spawnPositions.size());
}

void DeathmatchGameMode::initializeInterface() {
    cameraController.initialize();
    cameraController.focusOn({500, 500}, 1400, 0);

    hudElements = ObjectManager::GetInstance()->CreateGameObject("GUI");
    uiComponent = ObjectManager::GetInstance()->CreateComponent<DeathmatchUIComponent>(hudElements.get());
    uiComponent->setMaxScore(maxScore);
}

void DeathmatchGameMode::spawnRabbits() {
    redRabbit = std::make_unique<Rabbit>("red", spawnPositions[0], 0);
    blueRabbit = std::make_unique<Rabbit>("blue", spawnPositions[1], 1);
}

void DeathmatchGameMode::gameObjectDied(RabbitPhysicsComponent* rabbitPhysicsComponent) {
    if(rabbitPhysicsComponent->getGameObject()->name.compare("Rabbit_red") == 0) {
        if(isPlaying) scoreBlue++;
    } else if (rabbitPhysicsComponent->getGameObject()->name.compare("Rabbit_blue") == 0) {
        if(isPlaying) scoreRed++;
    }
    playersToRespawn.push_back(rabbitPhysicsComponent);
    if(scoreBlue >= maxScore || scoreRed >= maxScore) {
        isPlaying = false;
    }
}
