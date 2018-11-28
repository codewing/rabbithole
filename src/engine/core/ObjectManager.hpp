//
// Created by codewing on 08.11.18.
//

#pragma once


#include <vector>
#include <string>

#include "GameObject.hpp"
#include "CameraManager.hpp"
#include "IUpdatable.hpp"
#include "IRenderable.hpp"
#include "../component/PhysicsComponent.hpp"

class ObjectManager {

public:
    static ObjectManager* GetInstance();

    template<typename TComponent>
    std::shared_ptr<TComponent> CreateComponent(GameObject* gameObject) {
        std::shared_ptr<TComponent> component = std::make_shared<TComponent>(gameObject);

        componentList.push_back(component);

        if(ComponentFlag::UPDATE & component->type) {
            updatableComponents.push_back(std::dynamic_pointer_cast<IUpdatable>(component));
        }

        if(ComponentFlag::RENDERABLE & component->type) {
            renderableComponents.push_back(std::dynamic_pointer_cast<IRenderable>(component));
        }

        if(ComponentFlag::PHYSICS & component->type) {
            physicsComponents.push_back(std::dynamic_pointer_cast<PhysicsComponent>(component));
        }

        if(ComponentFlag::INPUT & component->type) {
            inputComponents.push_back(std::dynamic_pointer_cast<Component>(component));
        }

        gameObject->addComponent(component);

        return component;
    }

    std::shared_ptr<GameObject> CreateGameObject(std::string name);

    std::vector<std::shared_ptr<IRenderable>>& getRenderableComponents();
    std::vector<std::shared_ptr<PhysicsComponent>>& getPhysicsComponents();
    std::vector<std::shared_ptr<IUpdatable>>& getUpdatableComponents();

    CameraManager& getCameraManager();

private:
    static ObjectManager* instance;

    ObjectManager();

    CameraManager cameraManager;

    std::vector<std::shared_ptr<GameObject>> gameobjectList;
    std::vector<std::shared_ptr<Component>> componentList;

    std::vector<std::shared_ptr<IUpdatable>> updatableComponents;
    std::vector<std::shared_ptr<PhysicsComponent>> physicsComponents;
    std::vector<std::shared_ptr<IRenderable>> renderableComponents;
    std::vector<std::shared_ptr<Component>> inputComponents;
};
