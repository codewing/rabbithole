#include <sstream>
#include "PortalComponent.hpp"
#include "../engine/core/GameObject.hpp"
#include "../engine/debug/Log.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec2.hpp>
#include <glm/gtx/string_cast.hpp>

PortalComponent::PortalComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::PHYSICS | ComponentFlag::UPDATE) {
}

void PortalComponent::setOtherPortal(PortalComponent* portal){
	otherPortal = portal;
}

PortalComponent* PortalComponent::getOtherPortal(){
	return otherPortal;
}

void PortalComponent::onCollisionStart(IInteractable * interactable){

    if(std::find(teleportedObjects.begin(), teleportedObjects.end(), interactable) == teleportedObjects.end()) {
        auto otherPhysicsComponent = dynamic_cast<PhysicsComponent*>(interactable);
        if(otherPhysicsComponent != nullptr){
            otherPortal->addTeleportedObject(interactable);
            auto newPos = otherPortal->getPosition();
            otherPhysicsComponent->setPosition(newPos);
            objectsToTeleport.push_back(otherPhysicsComponent);
        }
    }

}

void PortalComponent::onCollisionEnd(IInteractable * interactable){
    auto it = std::find(teleportedObjects.begin(), teleportedObjects.end(), interactable);

    if(it != teleportedObjects.end()) {
        teleportedObjects.erase(it);
    }
}

void PortalComponent::addTeleportedObject(IInteractable *teleportedObject) {
    teleportedObjects.push_back(teleportedObject);
}

void PortalComponent::setPosition(glm::vec2 newPosition) {
    gameObject->setLocalPosition(newPosition);
}

void PortalComponent::setRotation(float newAngle) {
    gameObject->setLocalRotation(newAngle);
}

glm::vec2 PortalComponent::getPosition() {
    return gameObject->getPosition();
}

float PortalComponent::getRotation() {
    return gameObject->getRotation();
}

void PortalComponent::onUpdate(float deltaTime) {
    if(!objectsToTeleport.empty()) {
        std::for_each(objectsToTeleport.begin(), objectsToTeleport.end(), [&](PhysicsComponent* physicsComponent) {
            physicsComponent->teleport(otherPortal->getPosition(), physicsComponent->getGameObject()->getRotation());
        });

        objectsToTeleport.clear();
    }
}
