//
// Created by codewing on 09.12.18.
//

#include "WeaponControllerComponent.hpp"

#include "../engine/component/SpriteComponent.hpp"
#include "MovementComponent.hpp"
#include "../engine/debug/Log.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "Projectile.hpp"
#include <glm/gtx/vector_angle.hpp>

WeaponControllerComponent::WeaponControllerComponent(GameObject *gameObject) : Component(
        gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {}

void WeaponControllerComponent::setWeaponSprite(const sre::Sprite &weaponSprite) {
    WeaponControllerComponent::weaponSprite = weaponSprite;
}

void WeaponControllerComponent::onUpdate(float deltaTime) {
    if(fireCooldown >= 0.0f) fireCooldown -= deltaTime;

    float angle;
    // Prevent normalization NaN
    if(aimUp != 0.0 || aimRight != 0.0) {
        glm::vec2 aimingDirection = glm::normalize(glm::vec2{aimRight, -aimUp});
        angle = glm::angle(glm::vec2{0,-1}, aimingDirection);

        movementComponent->setIsAiming(true);

        if(aimRight < 0.0) {
            movementComponent->setIsFlippedDueToAiming(false);
            weaponSprite.setFlip({false, false});
            gameObject->setLocalRotation(180-(glm::degrees(angle) - 55));
        } else {
            movementComponent->setIsFlippedDueToAiming(true);
            weaponSprite.setFlip({true, false});
            gameObject->setLocalRotation(glm::degrees(angle) - 55);
        }

        // not only aim but also shoot!
        if(std::abs(aimUp) + std::abs(aimRight) >= 0.8) {
            fireProjectile(aimingDirection, gameObject->getParent()->getLocalPosition() + aimingDirection * 35.0f);
        }

    } else {
        weaponSprite.setFlip({movementComponent->isIsFlippedDueToMovement(), false});
        movementComponent->setIsAiming(false);
    }

    spriteComponent->setSprite(weaponSprite);

}

void WeaponControllerComponent::fireProjectile(glm::vec2 direction, glm::vec2 position) {
    if(fireCooldown < 0.0f) {
        Projectile::spawnProjectile(currentWeapon, direction, position);
        fireCooldown = currentWeapon.getFireCooldown();
    }
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
