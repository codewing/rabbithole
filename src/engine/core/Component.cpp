//
// Created by Morten Nobel-Jørgensen on 10/10/2017.
//

#include "Component.hpp"

Component::Component(GameObject *gameObject, uint8_t componentFlags)
    : gameObject(gameObject), type(componentFlags)
{
}

GameObject *Component::getGameObject() {
    return gameObject;
}
