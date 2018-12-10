//
// Created by codewing on 09.12.18.
//

#include "WeaponControllerComponent.hpp"

WeaponControllerComponent::WeaponControllerComponent(GameObject *gameObject) : Component(
        gameObject, ComponentFlag::UPDATE | ComponentFlag::INPUT) {}

void WeaponControllerComponent::setWeaponSprite(const sre::Sprite &weaponSprite) {
    WeaponControllerComponent::weaponSprite = weaponSprite;
}

void WeaponControllerComponent::onUpdate(float deltaTime) {

}

void WeaponControllerComponent::setReferenceToSpriteComponent(SpriteComponent *spriteComponent) {
    this->spriteComponent = spriteComponent;
}

bool WeaponControllerComponent::onControllerEvent(SDL_Event &event) {


    return true;
}

void WeaponControllerComponent::setControllerID(int controllerID) {
    this->controllerID = controllerID;
}
