//
// Created by codewing on 08.11.18.
//

#pragma once


#include <vector>
#include <string>

#include "GameObject.hpp"
#include "CameraManager.hpp"
#include "../component/SpriteComponent.hpp"
#include "../component/PhysicsComponent.hpp"

class ObjectManager {

public:
    static ObjectManager* GetInstance();

    template<typename TComponent>
    std::shared_ptr<TComponent> CreateComponent(GameObject* gameObject) {
        auto component = std::make_shared<TComponent>(gameObject);
        componentList.push_back(component);

        renderableComponents.push_back(component);
        
        gameObject->addComponent(component);

        return component;
    }

    std::shared_ptr<GameObject> CreateGameObject(std::string name);

    std::vector<std::shared_ptr<SpriteComponent>>& getRenderableComponents();
    std::vector<std::shared_ptr<PhysicsComponent>>& getPhysicsComponents();
    std::vector<std::shared_ptr<Component>>& getUpdatableComponents();

    CameraManager& getCameraManager();

private:
    static ObjectManager* instance;

    ObjectManager();

    CameraManager cameraManager;

    std::vector<std::shared_ptr<GameObject>> gameobjectList;
    std::vector<std::shared_ptr<Component>> componentList;

    std::vector<std::shared_ptr<Component>> updatableComponents;
    std::vector<std::shared_ptr<PhysicsComponent>> physicsComponents;
    std::vector<std::shared_ptr<SpriteComponent>> renderableComponents;
};
