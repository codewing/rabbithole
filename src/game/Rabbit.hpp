//
// Created by codewing on 04.12.18.
//

#pragma once


#include <glm/vec2.hpp>
#include "../engine/core/EngineCore.hpp"

class Rabbit {
public:
    Rabbit(EngineCore& engine, const std::string& team, glm::vec2 position, int gamepadID);

    glm::vec2 getPosition();

private:

    EngineCore& engine;
    std::string team;

    std::shared_ptr<GameObject> rabbitBase;
    std::shared_ptr<GameObject> rabbitWeapon;

    void spawnRabbitBase(glm::vec2 position, int gamepadID);
    void spawnRabbitWeapon(int gamepadID);
};

