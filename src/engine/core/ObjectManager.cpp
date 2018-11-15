//
// Created by codewing on 08.11.18.
//

#include "ObjectManager.hpp"

ObjectManager* ObjectManager::instance = 0;

std::vector<std::weak_ptr<SpriteComponent>> &ObjectManager::getRenderableComponents() {
    return renderableComponents;
}

std::vector<std::weak_ptr<PhysicsComponent>> &ObjectManager::getPhysicsComponents() {
    return physicsComponents;
}

std::vector<std::weak_ptr<Component>> &ObjectManager::getUpdatableComponents() {
    return updatableComponents;
}

ObjectManager* ObjectManager::GetInstance() {
    if (instance == nullptr)
    {
        instance = new ObjectManager();
    }

    return instance;
}

GameObject* ObjectManager::CreateGameObject(std::string name) {
    gameobjectList.push_back(GameObject{name});

    return &gameobjectList[gameobjectList.size()-1];
}

ObjectManager::ObjectManager() {}


