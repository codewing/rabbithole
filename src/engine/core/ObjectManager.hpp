//
// Created by codewing on 08.11.18.
//

#pragma once


#include <vector>
#include "GameObject.hpp"
#include "../component/SpriteComponent.hpp"
#include "../component/PhysicsComponent.hpp"

class ObjectManager {

public:
    static ObjectManager instance;

    std::vector<SpriteComponent>& getRenderableComponents();
    std::vector<PhysicsComponent>& getPhysicsComponents();

private:
    std::vector<GameObject> gameobjectList;

    std::vector<SpriteComponent> spriteComponentList;
    std::vector<PhysicsComponent> physicsComponentList;

};
