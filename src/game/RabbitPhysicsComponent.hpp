//
// Created by codewing on 06.12.18.
//

#pragma once

#include "../engine/component/PhysicsComponent.hpp"


class RabbitPhysicsComponent : public PhysicsComponent, public b2RayCastCallback {

public:
    RabbitPhysicsComponent(GameObject *gameObject);

    void checkGrounded();
    float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) override;

    void onCollisionStart(IInteractable *interactable) override;

    void onCollisionEnd(IInteractable *interactable) override;
};

