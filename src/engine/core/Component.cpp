//
// Created by Morten Nobel-Jørgensen on 10/10/2017.
//

#include "Component.hpp"

Component::Component(GameObject *gameObject, EComponentType type)
    : gameObject(gameObject), type(type)
{
}



void Component::update(float deltaTime) {

}

GameObject *Component::getGameObject() {
    return gameObject;
}

bool Component::onKey(SDL_Event &event) {
    return false;
}
