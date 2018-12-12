//
// Created by codewing on 12.12.18.
//

#pragma once


#include "../engine/component/PhysicsComponent.hpp"

class ProjectilePhysicsComponent : public PhysicsComponent {
public:
    ProjectilePhysicsComponent(GameObject *gameObject);

    void onCollisionStart(IInteractable *interactable) override;

private:
    std::vector<std::string> explosionSpriteNames = {"poof_1.png", "poof_2.png", "poof_3.png", "poof_4.png", "poof_5.png",
                                                 "poof_6.png", "poof_7.png", "poof_8.png", "poof_9.png", "poof_10.png",
                                                 "poof_11.png" };

    bool collided = false;
};

