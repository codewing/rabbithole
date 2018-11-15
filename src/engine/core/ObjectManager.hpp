//
// Created by codewing on 08.11.18.
//

#pragma once


#include <vector>
#include <string>

#include "GameObject.hpp"
#include "../component/SpriteComponent.hpp"
#include "../component/PhysicsComponent.hpp"

class ObjectManager {

public:
    static ObjectManager* GetInstance();

    template<typename TComponent>
    TComponent* CreateComponent(GameObject* gameObject) {
        componentList.push_back(std::move(TComponent(gameObject)));
        TComponent* comp = dynamic_cast<TComponent*>(&(componentList[componentList.size()-1]));

        // TODO gameObject->addComponent();

        return comp;
    }

    GameObject* CreateGameObject(std::string name);

    std::vector<std::weak_ptr<SpriteComponent>>& getRenderableComponents();
    std::vector<std::weak_ptr<PhysicsComponent>>& getPhysicsComponents();
    std::vector<std::weak_ptr<Component>>& getUpdatableComponents();

private:
    static ObjectManager* instance;

    ObjectManager();

    std::vector<GameObject> gameobjectList;
    std::vector<Component> componentList;

    std::vector<std::weak_ptr<Component>> updatableComponents;
    std::vector<std::weak_ptr<PhysicsComponent>> physicsComponents;
    std::vector<std::weak_ptr<SpriteComponent>> renderableComponents;
};
