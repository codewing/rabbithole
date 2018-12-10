//
// Created by codewing on 09.12.18.
//

#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IUpdatable.hpp"
#include "../engine/core/IInputable.hpp"

class SpriteComponent;

class WeaponControllerComponent : public Component, public IUpdatable, public IInputable {

public:
    WeaponControllerComponent(GameObject *gameObject);

    void onUpdate(float deltaTime) override;

    bool onControllerEvent(SDL_Event &event) override;

    void setWeaponSprite(const sre::Sprite &weaponSprite);
    void setReferenceToSpriteComponent(SpriteComponent *spriteComponent);
    void setControllerID(int controllerID);

private:
    sre::Sprite weaponSprite;
    SpriteComponent* spriteComponent;
    int controllerID;

    glm::vec2 aimingDirection = {0, 0};

};

