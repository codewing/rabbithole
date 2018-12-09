//
// Created by codewing on 06.12.18.
//

#pragma once

#include "../engine/component/PhysicsComponent.hpp"


class RabbitPhysicsComponent : public PhysicsComponent {

public:
    RabbitPhysicsComponent(GameObject *gameObject);

    void onCollisionStart(IInteractable *interactable) override;

    void onCollisionEnd(IInteractable *interactable) override;
};

