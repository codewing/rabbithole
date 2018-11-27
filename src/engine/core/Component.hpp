#pragma once

#include "sre/SpriteBatch.hpp"
#include "../component/ComponentType.hpp"

class GameObject;

class Component {                                           // Abstract class that adds behavior to a GameObject
public:
    explicit Component(GameObject* gameObject, uint8_t componentFlags);

    virtual ~Component() = default;
    GameObject* getGameObject();

    virtual void update(float deltaTime);

    const uint8_t type;

protected:
    GameObject* gameObject;

    friend class GameObject;
};

