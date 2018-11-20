//
// Created by codewing on 08.11.18.
//

#include "Physics.hpp"

#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "../component/PhysicsComponent.hpp"
#include "GameObject.hpp"

Physics::Physics() {
    initPhysics();
}

void Physics::initPhysics() {
    delete world;
    world = new b2World(b2Vec2(0, gravity));
    world->SetContactListener(this);
}

void Physics::BeginContact(b2Contact *contact) {
    handleContact(contact, true);
}

void Physics::EndContact(b2Contact *contact) {
    handleContact(contact, false);
}

void Physics::handleContact(b2Contact *contact, bool isBegin) {
    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
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

void Physics::update(float deltaTime) {
    timeAccumulator += deltaTime;

    while(timeAccumulator >= timeStep) {
        world->Step(timeStep, velocityIterations, positionIterations);

        for (auto phys : physicsComponentLookup){
            if (phys.second->rbType == b2_staticBody) continue;
            auto position = phys.second->body->GetPosition();
            float angle = phys.second->body->GetAngle();
            auto gameObject = phys.second->getGameObject();
            gameObject->setPosition(glm::vec2(position.x * PHYSICS_SCALE, position.y * PHYSICS_SCALE));
            gameObject->setRotation(angle);
        }

        timeAccumulator -= timeStep;
    }

}
