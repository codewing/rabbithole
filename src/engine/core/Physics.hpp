//
// Created by codewing on 08.11.18.
//

#pragma once

#include <map>

#include "Box2D/Dynamics/b2World.h"

class PhysicsComponent;

class Physics : public b2ContactListener {

public:

    Physics();

    static constexpr float PHYSICS_SCALE = 100;

    void update(float deltaTime);

private:
    const int positionIterations = 2;
    const int velocityIterations = 6;
    float gravity = -9.81f;

    const float timeStep = 0.2f;
    float timeAccumulator = 0.0f;

    b2World* world = nullptr;

    std::map<b2Fixture*, PhysicsComponent*> physicsComponentLookup;

    void initPhysics();

    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
    void handleContact(b2Contact *contact, bool isBegin);

    friend class SimpleRenderer;
};
