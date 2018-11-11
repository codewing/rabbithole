#pragma once

#include "sre/SpriteBatch.hpp"

// Forward declaration
class GameObject;


class Component {                                           // Abstract class that adds behavior to a GameObject
public:
    explicit Component(GameObject* gameObject);
    virtual ~Component() = default;
    GameObject* getGameObject();

    virtual bool onKey(SDL_Event &event);                   // The function should return true, if the key event is consumed. This prevents other components to receive the event.

    virtual void update(float deltaTime);

protected:
    GameObject* gameObject;

    friend class GameObject;
};

