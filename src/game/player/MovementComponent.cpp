//
// Created by codewing on 28.11.18.
//

#include <sstream>
#include "MovementComponent.hpp"
#include "../../engine/component/SpriteComponent.hpp"
#include "../../engine/core/GameObject.hpp"
#include "../../engine/debug/Log.hpp"
#include "RabbitPhysicsComponent.hpp"

MovementComponent::MovementComponent(GameObject *gameObject)
                : Component(gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {
    physicsComponent = gameObject->getComponent<RabbitPhysicsComponent>();
}

void MovementComponent::onUpdate(float deltaTime) {
    isGrounded = false;
    physicsComponent->checkGrounded();

    if(moveRight != 0) {
        physicsComponent->addImpulse(10 * deltaTime * glm::vec2{moveRight, 0});
    }

    if(jump) {
        physicsComponent->addImpulse(glm::vec2{0, 5});
        jump = false;
    }

    auto velocity = physicsComponent->getLinearVelocity();
    auto wasMoving = isMoving;
	// clamping the velocity to zero under a given threshold
    if(std::abs(velocity.x) < 0.05) {
        isMoving = false;
    } else {
        isMoving = true;
    }

    // Select and update animation frames depending on moving or not
    if(wasMoving != isMoving) {
        currentSpriteIndex = 0;
        currentTimeFrame = 0;
    } else {
        auto timePerFrame = isMoving ? movementTimeFrame : idleTimeFrame;
        currentTimeFrame += deltaTime;
        // Go to next frame when time passed
        if(currentTimeFrame > timePerFrame) {
            currentTimeFrame = 0;
            currentSpriteIndex++;
            auto numberOfSprites = static_cast<int>(isMoving ? movementSprites.size() : idleSprites.size());
            currentSpriteIndex = currentSpriteIndex % numberOfSprites;
        }
    }


    // Update selected Sprite and set flipped state
    sre::Sprite sprite;
    if(isMoving) {
        sprite = movementSprites[currentSpriteIndex];
    } else {
        sprite = idleSprites[currentSpriteIndex];
    }

    if(isAiming) {
        if(sprite.getFlip().x != isFlippedDueToAiming) {
            sprite.setFlip({isFlippedDueToAiming, false});
        }
    } else {
        if(velocity.x > 0.0) {
            sprite.setFlip({true, false});
            isFlippedDueToMovement = true;
        } else {
            isFlippedDueToMovement = false;
        }
    }

    spriteComponent->setSprite(sprite);

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

    if(event.type == SDL_CONTROLLERBUTTONDOWN) {
        if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A && isGrounded) {
            jump = true;
        }
    }

    if(event.type == SDL_CONTROLLERAXISMOTION) {
        if(event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
            moveRight = event.caxis.value / axisValueMax;
            if(std::abs(moveRight) < controllerDeadzone) {
                moveRight = 0;
            }
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

void MovementComponent::setupSprites(SpriteComponent* spriteComponent, std::vector<sre::Sprite> idleSprites, std::vector<sre::Sprite> movementSprites) {
    this->spriteComponent = spriteComponent;

    this->idleSprites = idleSprites;
    this->movementSprites = movementSprites;
}

void MovementComponent::setIsAiming(bool isAiming) {
    MovementComponent::isAiming = isAiming;
}

void MovementComponent::setIsFlippedDueToAiming(bool isFlippedDueToAiming) {
    MovementComponent::isFlippedDueToAiming = isFlippedDueToAiming;
}

bool MovementComponent::isIsFlippedDueToMovement() const {
    return isFlippedDueToMovement;
}
