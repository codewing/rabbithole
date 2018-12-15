//
// Created by codewing on 04.12.18.
//

#pragma once


#include <glm/vec2.hpp>
#include "../../engine/core/EngineCore.hpp"

class HealthComponent;
class RabbitPhysicsComponent;

class Rabbit {
public:
    Rabbit(const std::string& team, glm::vec2 position, int gamepadID);

    glm::vec2 getPosition();
    float getHealthValue();
    RabbitPhysicsComponent* getRabbitPhysicsComponent();

private:

    std::string team = "NO TEAM";

    std::shared_ptr<GameObject> rabbitBase = nullptr;
    std::shared_ptr<GameObject> rabbitWeapon = nullptr;

    std::shared_ptr<HealthComponent> healthComponent = nullptr;
    std::shared_ptr<RabbitPhysicsComponent> basePhysicsComponent = nullptr;

    void spawnRabbitBase(glm::vec2 position, int gamepadID);
    void spawnRabbitWeapon(int gamepadID);
};

