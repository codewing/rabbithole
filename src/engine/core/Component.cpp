#include "Component.hpp"

Component::Component(GameObject *gameObject, uint8_t componentFlags)
    : gameObject(gameObject), type(componentFlags)
{
}

GameObject *Component::getGameObject() {
    return gameObject;
}
