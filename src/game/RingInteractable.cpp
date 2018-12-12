//
// Created by codewing on 29.11.18.
//

#include "RingInteractable.hpp"
#include "TerrainUtils.hpp"
#include "WorldComponent.hpp"

#include "../engine/debug/Log.hpp"
#include "ProjectilePhysicsComponent.hpp"

void RingInteractable::onCollisionStart(IInteractable *interactable) {
    auto projectile = dynamic_cast<ProjectilePhysicsComponent*>(interactable);

    if(projectile != nullptr) {
        auto boostRing = TerrainUtils::makeConvexRing(b2Vec2{interactable->getPosition().x, interactable->getPosition().y}, 64, 8);
        worldComponent->registerRemoveShapeFromRing(this, boostRing);
    }
}

void RingInteractable::onCollisionEnd(IInteractable *interactable) {

}

void RingInteractable::setPosition(glm::vec2 newPosition) {}

void RingInteractable::setRotation(float newAngle) {}

RingInteractable::RingInteractable(WorldComponent* worldComponent, std::vector<b2Vec2> ringData)
    : worldComponent(worldComponent), ringData(ringData) {
    initChain(b2BodyType::b2_staticBody, ringData, {0, 0}, 1);
}

std::vector<b2Vec2> const RingInteractable::getRingData() {
    return ringData;
}

glm::vec2 RingInteractable::getPosition() {
    return glm::vec2();
}
