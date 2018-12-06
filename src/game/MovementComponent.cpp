//
// Created by codewing on 28.11.18.
//

#include <sstream>
#include "MovementComponent.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/debug/Log.hpp"

MovementComponent::MovementComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {
    physicsComponent = gameObject->getComponent<PhysicsComponent>();
}

void MovementComponent::onUpdate(float deltaTime) {
    if(moveRight != 0) {
        physicsComponent->addImpulse(10 * deltaTime * glm::vec2{moveRight, 0});
    }

    if(jump) {
        physicsComponent->addImpulse(glm::vec2{0, 5});
        jump = false;
    }
}

bool MovementComponent::onKeyEvent(SDL_Event &event) {

    if(event.key.state == SDL_PRESSED) {
        if(event.key.keysym.sym == SDLK_SPACE && isGrounded) {
            jump = true;
        }
		
        if(event.key.keysym.sym == SDLK_d) {
            moveRight = 1;
        }
		
        if(event.key.keysym.sym == SDLK_a) {
            moveRight = -1;
        }

    } else {
        if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
            moveRight = 0;
        }
    }


    return true;
}

void MovementComponent::setGrounded(bool value)
{
	isGrounded = value;
}
