//
// Created by codewing on 28.11.18.
//

#include "MovementComponent.hpp"

MovementComponent::MovementComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {}

void MovementComponent::onUpdate(float deltaTime) {
}

bool MovementComponent::onKeyEvent(SDL_Event &event) {

    if(event.key.keysym.sym == SDLK_SPACE) {
        LOG_INFO("SPACED OUT");
    }

    return true;
}
