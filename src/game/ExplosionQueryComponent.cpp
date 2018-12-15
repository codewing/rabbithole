//
// Created by codewing on 15.12.18.
//

#include "ExplosionQueryComponent.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "player/HealthComponent.hpp"
#include "../engine/debug/Log.hpp"

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
                healthComponent->applyDamage(50);
            }
        }
    }

    return true;
}

void ExplosionQueryComponent::explode(float explosionRadius, glm::vec2 center) {
    auto b2Center = b2Vec2{center.x / PhysicsSystem::PHYSICS_SCALE, center.y / PhysicsSystem::PHYSICS_SCALE};
    auto offset = b2Vec2{explosionRadius / PhysicsSystem::PHYSICS_SCALE, explosionRadius / PhysicsSystem::PHYSICS_SCALE};

    b2AABB aabb;
    aabb.lowerBound = b2Center - offset;
    aabb.upperBound = b2Center + offset;
    world->QueryAABB(this, aabb);
}
