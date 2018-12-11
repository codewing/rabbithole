//
// Created by codewing on 09.12.18.
//

#include "WeaponControllerComponent.hpp"

#include "../engine/component/SpriteComponent.hpp"
#include "MovementComponent.hpp"
#include "../engine/debug/Log.hpp"
#include "../engine/core/ObjectManager.hpp"

WeaponControllerComponent::WeaponControllerComponent(GameObject *gameObject) : Component(
        gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {}

void WeaponControllerComponent::setWeaponSprite(const sre::Sprite &weaponSprite) {
    WeaponControllerComponent::weaponSprite = weaponSprite;
}

void WeaponControllerComponent::onUpdate(float deltaTime) {

    // Prevent normalization NaN
    if(aimUp != 0.0 || aimRight != 0.0) {
        glm::vec2 aimingDirection = glm::normalize(glm::vec2{aimUp, aimRight});
        movementComponent->setIsAiming(true);

        if(aimRight < 0.0) {
            movementComponent->setIsFlippedDueToAiming(false);
            weaponSprite.setFlip({false, false});
        } else {
            movementComponent->setIsFlippedDueToAiming(true);
            weaponSprite.setFlip({true, false});
        }

        // not only aim but also shoot!
        if(aimUp + aimRight >= 0.8) {
            fireProjectile(aimingDirection);
        }

    } else {
        weaponSprite.setFlip({movementComponent->isIsFlippedDueToMovement(), false});
        movementComponent->setIsAiming(false);
    }

    spriteComponent->setSprite(weaponSprite);

}

void WeaponControllerComponent::fireProjectile(glm::vec2 direction) {
    std::shared_ptr<GameObject> projectile = ObjectManager::GetInstance()->CreateGameObject("Projectile");

    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(projectile.get());

}

void WeaponControllerComponent::setReferenceToSpriteComponent(SpriteComponent *spriteComponent) {
    this->spriteComponent = spriteComponent;
}

bool WeaponControllerComponent::onControllerEvent(SDL_Event &event) {
    // skip execution if id doesnt match
    if(event.cdevice.which != gamepadID) return false;

    if(event.type == SDL_CONTROLLERAXISMOTION) {
        if(event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
            aimRight = event.caxis.value / axisValueMax;
            if(std::abs(aimRight) < controllerDeadzone) {
                aimRight = 0;
            }
        }

        if(event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
            aimUp = event.caxis.value / axisValueMax;
            if(std::abs(aimUp) < controllerDeadzone) {
                aimUp = 0;
            }
        }
    }


    return true;
}

void WeaponControllerComponent::setGamepadID(int gamepadID) {
    this->gamepadID = gamepadID;
}

void WeaponControllerComponent::setMovementComponent(MovementComponent* movementComponent) {
    WeaponControllerComponent::movementComponent = movementComponent;
}
