//
// Created by codewing on 09.12.18.
//

#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IUpdatable.hpp"
#include "../engine/core/IInputable.hpp"

class SpriteComponent;
class MovementComponent;

class WeaponControllerComponent : public Component, public IUpdatable, public IInputable {

public:
    WeaponControllerComponent(GameObject *gameObject);

    void onUpdate(float deltaTime) override;

    bool onControllerEvent(SDL_Event &event) override;

    void setWeaponSprite(const sre::Sprite &weaponSprite);
    void setReferenceToSpriteComponent(SpriteComponent *spriteComponent);
    void setGamepadID(int gamepadID);

    void setMovementComponent(MovementComponent *movementComponent);

private:
    sre::Sprite weaponSprite;
    SpriteComponent* spriteComponent;
    MovementComponent* movementComponent;

    int gamepadID = -1;
    static constexpr float axisValueMax = 32768;
    static constexpr float controllerDeadzone = 0.1;

    float aimRight, aimUp;

    void fireProjectile(glm::vec2 direction, glm::vec2 position);
};

