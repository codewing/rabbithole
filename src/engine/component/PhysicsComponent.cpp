//

#include <iostream>
#include "PhysicsComponent.hpp"
#include "../../game/MovementComponent.hpp"
#include "../core/GameObject.hpp"

PhysicsComponent::PhysicsComponent(GameObject *gameObject)
        : Component(gameObject, ComponentFlag::PHYSICS) {}


PhysicsComponent::~PhysicsComponent() {}


void PhysicsComponent::onCollisionStart(IInteractable *interactable) {
	std::shared_ptr<MovementComponent> mc = std::dynamic_pointer_cast<MovementComponent>(gameObject->getComponent<MovementComponent>());
	mc.get()->setGrounded(true);
}

void PhysicsComponent::onCollisionEnd(IInteractable *interactable) {
	std::shared_ptr<MovementComponent> mc = std::dynamic_pointer_cast<MovementComponent>(gameObject->getComponent<MovementComponent>());
	mc.get()->setGrounded(false);
}

void PhysicsComponent::setPosition(glm::vec2 newPosition) {
    gameObject->setPosition(newPosition);
}

void PhysicsComponent::setRotation(float newAngle) {
    gameObject->setRotation(newAngle);
}
