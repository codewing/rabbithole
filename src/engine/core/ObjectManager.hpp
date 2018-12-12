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
#include "IInputable.hpp"
#include "../component/PhysicsComponent.hpp"


class EngineCore;
class TextureSystem;

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

        if(ComponentFlag::INPUT & component->type) {
            inputComponents.push_back(std::dynamic_pointer_cast<IInputable>(component));
        }

        gameObject->addComponent(component);

        return component;
    }

    std::shared_ptr<GameObject> CreateGameObject(std::string name);

    void EnablePhysics(IInteractable *interactable);
    void DisablePhysics(IInteractable *interactable);
    b2World* GetPhysicsWorld();

    std::vector<std::shared_ptr<IRenderable>>& GetRenderableComponents();
    std::map<b2Fixture*, IInteractable*>& GetRegisteredPhysicsComponents();
    std::vector<std::shared_ptr<IUpdatable>>& GetUpdatableComponents();
    std::vector<std::shared_ptr<IInputable>>& GetInputComponents();

    CameraManager& GetCameraManager();
    TextureSystem& GetTextureSystem();

private:
    static ObjectManager* instance;

    ObjectManager();
    void setEngineCore(EngineCore* engineCore);

    CameraManager cameraManager;
    EngineCore* engineCore;

    std::vector<std::shared_ptr<GameObject>> gameobjectList;
    std::vector<std::shared_ptr<Component>> componentList;

    std::vector<std::shared_ptr<IUpdatable>> updatableComponents;
    std::map<b2Fixture*, IInteractable*> registeredPhysicsComponents;
    std::vector<std::shared_ptr<IRenderable>> renderableComponents;
    std::vector<std::shared_ptr<IInputable>> inputComponents;

    friend class EngineCore;
};
