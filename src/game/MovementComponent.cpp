//
// Created by codewing on 28.11.18.
//

#include <sstream>
#include "MovementComponent.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/debug/Log.hpp"

MovementComponent::MovementComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {}

void MovementComponent::onUpdate(float deltaTime) {

    auto pos = gameObject->getPosition() + glm::vec2{moveRight * 10 * deltaTime, moveUp * 10 * deltaTime};
    gameObject->setPosition(pos);
}

bool MovementComponent::onKeyEvent(SDL_Event &event) {

    if(event.key.state == SDL_PRESSED) {
        if(event.key.keysym.sym == SDLK_w) {
            moveUp = 1;
        }

        if(event.key.keysym.sym == SDLK_s) {
            moveUp = -1;
        }

        if(event.key.keysym.sym == SDLK_d) {
            moveRight = 1;
        }

        if(event.key.keysym.sym == SDLK_a) {
            moveRight = -1;
        }

    } else {
        if(event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s) {
            moveUp = 0;
        }

        if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
            moveRight = 0;
        }
    }


    return true;
}
