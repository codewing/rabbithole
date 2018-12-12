//
// Created by codewing on 08.11.18.
//

#include "ObjectManager.hpp"
#include "EngineCore.hpp"

#include "TextureSystem.hpp"
#include "../debug/Log.hpp"

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

void ObjectManager::DestroyGameObject(GameObject* gameobject) {
    gameobjectToDelete.push_back(gameobject);
}

void ObjectManager::DestroyComponent(Component* component) {
    componentToDelete.push_back(component);
}

void ObjectManager::DestroyGameObjectImmediately(GameObject *gameobject) {
    // first make sure that every component is destroyed
    while(!gameobject->getComponents().empty()) {
        std::shared_ptr<Component> component = gameobject->getComponents()[0];
        DestroyComponentImmediately(component.get());
    }

    // then destroy the gameobject
    auto findGo = [gameobject](std::shared_ptr<GameObject> currentGO) {
        return currentGO.get() == gameobject;
    };
    auto iter(remove_if(gameobjectList.begin(), gameobjectList.end(), findGo));
    gameobjectList.erase(iter);
}

void ObjectManager::DestroyComponentImmediately(Component *component) {
    component->getGameObject()->removeComponent(component);

    // Remove from lists depending on flags
    if(ComponentFlag::UPDATE & component->type) {
        IUpdatable* updatable = dynamic_cast<IUpdatable*>(component);
        if(updatable != nullptr) {
            auto findUpdatable = [updatable](std::shared_ptr<IUpdatable> iUpdatable) { return iUpdatable.get() == updatable;};
            auto iter(remove_if(updatableComponents.begin(), updatableComponents.end(), findUpdatable));
            updatableComponents.erase(iter);
        }
    }

    if(ComponentFlag::RENDERABLE & component->type) {
        IRenderable* renderable = dynamic_cast<IRenderable*>(component);
        if(renderable != nullptr) {
            auto findRenderable = [renderable](std::shared_ptr<IRenderable> iRenderable) { return iRenderable.get() == renderable;};
            auto iter(remove_if(renderableComponents.begin(), renderableComponents.end(), findRenderable));
            renderableComponents.erase(iter);
        }
    }

    if(ComponentFlag::INPUT & component->type) {
        IInputable* inputable = dynamic_cast<IInputable*>(component);
        if(inputable != nullptr) {
            auto findInputComponent = [inputable](std::shared_ptr<IInputable> iInputable) { return iInputable.get() == inputable;};
            auto iter(remove_if(inputComponents.begin(), inputComponents.end(), findInputComponent));
            inputComponents.erase(iter);
        }
    }

    auto findComponent = [component](std::shared_ptr<Component> currComponent) { return currComponent.get() == component;};
    auto iter(remove_if(componentList.begin(), componentList.end(), findComponent));
    componentList.erase(iter);
}

void ObjectManager::Cleanup() {
    if(!componentToDelete.empty()) {
        for(Component* comp : componentToDelete) {
            DestroyComponentImmediately(comp);
        }
        componentToDelete.clear();
    }

    if(!gameobjectToDelete.empty()) {
        for(GameObject* go : gameobjectToDelete) {
            DestroyGameObjectImmediately(go);
        }
        gameobjectToDelete.clear();
    }
}

