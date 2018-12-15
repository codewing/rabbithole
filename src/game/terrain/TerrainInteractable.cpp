//
// Created by codewing on 29.11.18.
//

#include "TerrainInteractable.hpp"
#include "TerrainUtils.hpp"
#include "WorldComponent.hpp"

#include "../../engine/debug/Log.hpp"
#include "../ProjectilePhysicsComponent.hpp"

void TerrainInteractable::onCollisionStart(IInteractable *interactable) {
    auto projectile = dynamic_cast<ProjectilePhysicsComponent*>(interactable);

    if(projectile != nullptr && !isBeingUpdated) {
        isBeingUpdated = true;
        auto position = projectile->getPhysicsLocation() * PhysicsSystem::PHYSICS_SCALE;
        auto boostRing = TerrainUtils::makeConvexRing(position, 64, 12);
        worldComponent->registerRemoveShapeFromRing(this, boostRing);
    }
}

void TerrainInteractable::onCollisionEnd(IInteractable *interactable) {

}

void TerrainInteractable::setPosition(glm::vec2 newPosition) {}

void TerrainInteractable::setRotation(float newAngle) {}

TerrainInteractable::TerrainInteractable(WorldComponent* worldComponent, std::vector<b2Vec2> terrainData)
    : worldComponent(worldComponent), terrainData(terrainData) {
    initChain(b2BodyType::b2_staticBody, this->terrainData, {0, 0}, 1);
}

std::vector<b2Vec2>& TerrainInteractable::getTerrainData() {
    return terrainData;
}

glm::vec2 TerrainInteractable::getPosition() {
    return glm::vec2();
}
