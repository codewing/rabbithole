//
// Created by codewing on 08.11.18.
//

#include "ObjectManager.hpp"

ObjectManager* ObjectManager::instance = 0;



ObjectManager* ObjectManager::GetInstance() {
    if (instance == nullptr)
    {
        instance = new ObjectManager();
    }

    return instance;
}

std::shared_ptr<GameObject> ObjectManager::CreateGameObject(std::string name) {
    auto go = std::make_shared<GameObject>(name);
    gameobjectList.push_back(go);

    return go;
}

ObjectManager::ObjectManager() {}

CameraManager &ObjectManager::getCameraManager() {
    return cameraManager;
}

std::vector<std::shared_ptr<IRenderable>> &ObjectManager::getRenderableComponents() {
    return renderableComponents;
}

std::vector<std::shared_ptr<PhysicsComponent>> &ObjectManager::getPhysicsComponents() {
    return physicsComponents;
}

std::vector<std::shared_ptr<IUpdatable>> &ObjectManager::getUpdatableComponents() {
    return updatableComponents;
}

std::vector<std::shared_ptr<IInputable>> &ObjectManager::getInputComponents() {
    return inputComponents;
}


