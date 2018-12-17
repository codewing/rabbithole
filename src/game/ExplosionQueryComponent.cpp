//
// Created by codewing on 15.12.18.
//

#include "ExplosionQueryComponent.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "player/HealthComponent.hpp"
#include "../engine/debug/Log.hpp"

#include <glm/glm.hpp>

/*
	class generating and managing explosions:
	- creating explosion + physics consequences (impulses)
	- creating and managing damage wrt distance from target
*/

ExplosionQueryComponent::ExplosionQueryComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::NONE) {
    world = ObjectManager::GetInstance()->GetPhysicsWorld();
}

bool ExplosionQueryComponent::ReportFixture(b2Fixture *fixture) {

    auto& physicsComponentLookup = ObjectManager::GetInstance()->GetRegisteredPhysicsComponents();
    auto fixtureEntry = physicsComponentLookup.find(fixture);

    if(fixtureEntry != physicsComponentLookup.end()) {
        auto physicsComponent = dynamic_cast<PhysicsComponent*>(fixtureEntry->second);
        if(physicsComponent != nullptr) {
            auto healthComponent = physicsComponent->getGameObject()->getComponent<HealthComponent>();
            if(healthComponent != nullptr) {
                glm::vec2 playerPos = glm::vec2{physicsComponent->getPosition().x, physicsComponent->getPosition().y} / PhysicsSystem::PHYSICS_SCALE;
                glm::vec2 explosionPos = glm::vec2{explosionLocation.x, explosionLocation.y};
                physicsComponent->addImpulse(glm::normalize(playerPos - explosionPos) * 10.0f);

                auto distanceToExplosion = glm::distance(playerPos, explosionPos) * PhysicsSystem::PHYSICS_SCALE;
                distanceToExplosion -= 32;  // subtract min distance
                distanceToExplosion /= 32.0f; // divide by radius to map to 0 -> 1
                healthComponent->applyDamage(55 * (1-distanceToExplosion));
            }
        }
    }

    return true;
}

void ExplosionQueryComponent::explode(float explosionRadius, glm::vec2 center) {
    ExplosionQueryComponent::radius = explosionRadius;
    explosionLocation = b2Vec2{center.x / PhysicsSystem::PHYSICS_SCALE, center.y / PhysicsSystem::PHYSICS_SCALE};
    auto offset = b2Vec2{explosionRadius / PhysicsSystem::PHYSICS_SCALE, explosionRadius / PhysicsSystem::PHYSICS_SCALE};

    b2AABB aabb;
    aabb.lowerBound = explosionLocation - offset;
    aabb.upperBound = explosionLocation + offset;
    world->QueryAABB(this, aabb);
}
