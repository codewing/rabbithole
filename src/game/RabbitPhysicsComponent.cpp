//
// Created by codewing on 06.12.18.
//

#include "RabbitPhysicsComponent.hpp"
#include "MovementComponent.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/debug/Log.hpp"

RabbitPhysicsComponent::RabbitPhysicsComponent(GameObject *gameObject) : PhysicsComponent(gameObject) {}

void RabbitPhysicsComponent::onCollisionStart(IInteractable *interactable) {
    std::shared_ptr<MovementComponent> mc = std::dynamic_pointer_cast<MovementComponent>(gameObject->getComponent<MovementComponent>());
    mc.get()->setGrounded(true);
    LOG_GAME_INFO("Grounded!");
}

void RabbitPhysicsComponent::onCollisionEnd(IInteractable *interactable) {
    std::shared_ptr<MovementComponent> mc = std::dynamic_pointer_cast<MovementComponent>(gameObject->getComponent<MovementComponent>());
    mc.get()->setGrounded(false);
    LOG_GAME_INFO("NotGrounded!");
}
