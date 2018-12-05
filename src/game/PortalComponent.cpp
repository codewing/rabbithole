#include <sstream>
#include "PortalComponent.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/debug/Log.hpp"

PortalComponent::PortalComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::PHYSICS) {
}

void PortalComponent::setOtherPortal(std::shared_ptr<GameObject> gameObject){
	otherPortal = gameObject;
}

std::shared_ptr<GameObject> PortalComponent::getOtherPortal(){
	return otherPortal;
}

void PortalComponent::onCollisionStart(IInteractable * interactable){
}

void PortalComponent::onCollisionEnd(IInteractable * interactable){
}

void PortalComponent::setPosition(glm::vec2 newPosition){
	gameObject->setPosition(newPosition);
}

void PortalComponent::setRotation(float newAngle){
	gameObject->setRotation(newAngle);
}
