//
// Created by codewing on 08.11.18.
//

#include "ObjectManager.hpp"

std::vector<SpriteComponent> &ObjectManager::getRenderableComponents() {
    return spriteComponentList;
}

std::vector<PhysicsComponent> &ObjectManager::getPhysicsComponents() {
    return physicsComponentList;
}
