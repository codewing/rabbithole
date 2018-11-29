//
// Created by codewing on 08.11.18.
//

#include "PhysicsSystem.hpp"

#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "../component/PhysicsComponent.hpp"
#include "GameObject.hpp"
#include "ObjectManager.hpp"

PhysicsSystem::PhysicsSystem() {
    initPhysics();
}

void PhysicsSystem::initPhysics() {
    delete world;
    world = new b2World(b2Vec2(0, gravity));
    world->SetContactListener(this);
}

void PhysicsSystem::BeginContact(b2Contact *contact) {
    handleContact(contact, true);
}

void PhysicsSystem::EndContact(b2Contact *contact) {
    handleContact(contact, false);
}

void PhysicsSystem::handleContact(b2Contact *contact, bool isBegin) {
    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
    auto& physicsComponentLookup = ObjectManager::GetInstance()->GetRegisteredPhysicsComponents();

    auto physA = physicsComponentLookup.find(fixA);
    auto physB = physicsComponentLookup.find(fixB);
    if (physA !=physicsComponentLookup.end() && physB != physicsComponentLookup.end()){
        if (isBegin){
            physA->second->onCollisionStart(physB->second);
            physB->second->onCollisionStart(physA->second);
        } else {
            physA->second->onCollisionEnd(physB->second);
            physB->second->onCollisionEnd(physA->second);
        }

    }

}

void PhysicsSystem::update(float deltaTime) {
    timeAccumulator += deltaTime;
    auto& physicsComponentLookup = ObjectManager::GetInstance()->GetRegisteredPhysicsComponents();

    while(timeAccumulator >= timeStep) {
        world->Step(timeStep, velocityIterations, positionIterations);

        for (auto phys : physicsComponentLookup){
            if (phys.second->rbType == b2_staticBody) continue;
            auto newPosition = phys.second->body->GetPosition();
            float newAngle = phys.second->body->GetAngle();

            auto interactable = phys.second;
            interactable->setPosition(glm::vec2(newPosition.x * PHYSICS_SCALE, newPosition.y * PHYSICS_SCALE));
            interactable->setRotation(newAngle);
        }

        timeAccumulator -= timeStep;
    }

}
