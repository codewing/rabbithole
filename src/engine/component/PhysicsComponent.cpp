//

#include "PhysicsComponent.hpp"
#include "../core/GameObject.hpp"

PhysicsComponent::PhysicsComponent(GameObject *gameObject)
        : Component(gameObject, ComponentFlag::PHYSICS) {}


PhysicsComponent::~PhysicsComponent() {}


void PhysicsComponent::onCollisionStart(IInteractable *interactable) {}

void PhysicsComponent::onCollisionEnd(IInteractable *interactable) {}

void PhysicsComponent::setPosition(glm::vec2 newPosition) {
    gameObject->setLocalPosition(newPosition);
}

void PhysicsComponent::setRotation(float newAngle) {
    gameObject->setLocalRotation(newAngle);
}
