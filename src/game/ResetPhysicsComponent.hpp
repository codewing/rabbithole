//
// Created by codewing on 14/12/2018.
//


#pragma once


#include "../engine/component/PhysicsComponent.hpp"

class DeathmatchGameMode;

class ResetPhysicsComponent : public PhysicsComponent {
public:
    ResetPhysicsComponent(GameObject *gameObject);
    void onCollisionStart(IInteractable *interactable) override;

    void setGameMode(DeathmatchGameMode* gameMode);

private:
    DeathmatchGameMode* gameMode;
};



