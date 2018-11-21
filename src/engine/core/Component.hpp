#pragma once

#include "sre/SpriteBatch.hpp"
#include "../component/EComponentType.hpp"

class GameObject;

class Component {                                           // Abstract class that adds behavior to a GameObject
public:
    explicit Component(GameObject* gameObject, EComponentType type);

    virtual ~Component() = default;
    GameObject* getGameObject();
    virtual bool onKey(SDL_Event &event);                   // The function should return true, if the key event is consumed. This prevents other components to receive the event.

    virtual void update(float deltaTime);

    const EComponentType type;

protected:
    GameObject* gameObject;

    friend class GameObject;
};

