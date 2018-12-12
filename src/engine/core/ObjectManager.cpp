//
// Created by codewing on 08.11.18.
//

#include "ObjectManager.hpp"
#include "EngineCore.hpp"

#include "TextureSystem.hpp"

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

CameraManager &ObjectManager::GetCameraManager() {
    return cameraManager;
}

std::vector<std::shared_ptr<IRenderable>> &ObjectManager::GetRenderableComponents() {
    return renderableComponents;
}

std::vector<std::shared_ptr<IUpdatable>> &ObjectManager::GetUpdatableComponents() {
    return updatableComponents;
}

std::vector<std::shared_ptr<IInputable>> &ObjectManager::GetInputComponents() {
    return inputComponents;
}

void ObjectManager::setEngineCore(EngineCore* engineCore) {
    this->engineCore = engineCore;
}

void ObjectManager::EnablePhysics(IInteractable *interactable) {
    registeredPhysicsComponents[interactable->fixture] = interactable;
}

void ObjectManager::DisablePhysics(IInteractable *interactable) {
    auto iter = registeredPhysicsComponents.find(interactable->fixture);
    if (iter != registeredPhysicsComponents.end()){
        registeredPhysicsComponents.erase(iter);
    } else {
        assert(false); // cannot find physics object
    }
}

std::map<b2Fixture *, IInteractable *> &ObjectManager::GetRegisteredPhysicsComponents() {
    return registeredPhysicsComponents;
}

b2World *ObjectManager::GetPhysicsWorld() {
    return engineCore->getPhysicsSystem().world;
}

TextureSystem &ObjectManager::GetTextureSystem() {
    return engineCore->getGraphicsSystem().getTextureSystem();
}

