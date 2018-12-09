//
// Created by codewing on 28.11.18.
//

#include <sstream>
#include "MovementComponent.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/debug/Log.hpp"

MovementComponent::MovementComponent(GameObject *gameObject)
                : Component(gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {
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
    // skip execution if using controller doesnt match
    if(gamepadID != -1) return false;

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

bool MovementComponent::onControllerEvent(SDL_Event &event) {
    // skip execution if id doesnt match
    if(event.cdevice.which != gamepadID) return false;

    if(event.cbutton.state == SDL_PRESSED) {
        if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A && isGrounded) {
            jump = true;
        }
    }

    if(event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {

        moveRight = event.caxis.value / axisValueMax;
        if(std::abs(moveRight) < controllerDeadzone) {
            moveRight = 0;
        }
    }

    return true;
}

void MovementComponent::setupControllerInput(int gamepadID) {
    this->gamepadID = gamepadID;
    if(gamepadID != -1) {
        if (SDL_IsGameController(gamepadID))
        {
            controllerHandle = SDL_GameControllerOpen(gamepadID);

            if(controllerHandle == NULL) {
                controllerHandle = nullptr;
                LOG_GAME_WARN("SDL_ERROR: Could NOT open the gamepad with id " + std::to_string(gamepadID));
            }
        } else {
            LOG_GAME_WARN("SDL_ERROR: Not a gamepad (id: " + std::to_string(gamepadID) + ")");
        }
    }
}

MovementComponent::~MovementComponent() {
    if(controllerHandle != nullptr) {
        SDL_GameControllerClose(controllerHandle);
        controllerHandle = nullptr;
    }
}
