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
    TComponent* CreateComponent(GameObject* gameObject) {
        auto component = TComponent(gameObject);
        componentList.push_back(std::move(component));
        auto lastElement = &(componentList[componentList.size()-1]);
        TComponent* comp = static_cast<TComponent*>(lastElement);
        
        gameObject->addComponent(comp);

        return comp;
    }

    GameObject* CreateGameObject(std::string name);

    std::vector<SpriteComponent*>& getRenderableComponents();
    std::vector<PhysicsComponent*>& getPhysicsComponents();
    std::vector<Component*>& getUpdatableComponents();

    CameraManager& getCameraManager();

private:
    static ObjectManager* instance;

    ObjectManager();

    CameraManager cameraManager;

    std::vector<GameObject> gameobjectList;
    std::vector<Component> componentList;

    std::vector<Component*> updatableComponents;
    std::vector<PhysicsComponent*> physicsComponents;
    std::vector<SpriteComponent*> renderableComponents;
};
