//
// Created by codewing on 14/12/2018.
//

#include "ResetPhysicsComponent.hpp"

#include "DeathmatchGameMode.hpp"
#include "RabbitPhysicsComponent.hpp"

void ResetPhysicsComponent::onCollisionStart(IInteractable *interactable) {
    auto rabbitPhysicsComponent = dynamic_cast<RabbitPhysicsComponent*>(interactable);
    if(rabbitPhysicsComponent != nullptr) {
        gameMode->gameObjectDied(rabbitPhysicsComponent);
    }
}

ResetPhysicsComponent::ResetPhysicsComponent(GameObject *gameObject) : PhysicsComponent(gameObject) {}

void ResetPhysicsComponent::setGameMode(DeathmatchGameMode *gameMode) {
    ResetPhysicsComponent::gameMode = gameMode;
}
