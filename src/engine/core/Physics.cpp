//
// Created by codewing on 08.11.18.
//

#include "Physics.hpp"

Physics::Physics() {
    initPhysics();
}

void Physics::initPhysics() {
    float gravity = -9.8f;
    delete world;
    world = new b2World(b2Vec2(0,gravity));
    world->SetContactListener(this);

}
