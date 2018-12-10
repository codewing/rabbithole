//
// Created by codewing on 06.12.18.
//

#include "MovementComponent.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/debug/Log.hpp"

RabbitPhysicsComponent::RabbitPhysicsComponent(GameObject *gameObject) : PhysicsComponent(gameObject) {}

void RabbitPhysicsComponent::onCollisionStart(IInteractable *interactable) {
    if(!interactable->isSensor()) {
        std::shared_ptr<MovementComponent> mc = std::dynamic_pointer_cast<MovementComponent>(gameObject->getComponent<MovementComponent>());
        mc.get()->setGrounded(true);
    }
}

void RabbitPhysicsComponent::onCollisionEnd(IInteractable *interactable) {
    if(!interactable->isSensor()) {
        std::shared_ptr<MovementComponent> mc = std::dynamic_pointer_cast<MovementComponent>(gameObject->getComponent<MovementComponent>());
        mc.get()->setGrounded(false);
    }
}

void RabbitPhysicsComponent::checkGrounded() {
    auto from = body->GetWorldCenter();
    b2Vec2 target1 {from.x - 15 / PhysicsSystem::PHYSICS_SCALE,from.y - (32 / PhysicsSystem::PHYSICS_SCALE) * 1.5f};
    b2Vec2 target2 {from.x + 15 / PhysicsSystem::PHYSICS_SCALE,from.y - (32 / PhysicsSystem::PHYSICS_SCALE) * 1.5f};
    world->RayCast(this, from, target1);
}

float32
RabbitPhysicsComponent::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) {
    std::shared_ptr<MovementComponent> mc = std::dynamic_pointer_cast<MovementComponent>(gameObject->getComponent<MovementComponent>());
    mc.get()->setGrounded(true);
    return 0;
}
