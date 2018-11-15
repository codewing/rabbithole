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
    const float32 timeStep = 1.0f / 60.0f;
    const int positionIterations = 2;
    const int velocityIterations = 6;

    b2World* world = nullptr;

    std::map<b2Fixture*, PhysicsComponent*> physicsComponentLookup;

    void initPhysics();

    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
    void handleContact(b2Contact *contact, bool isBegin);

    friend class SimpleRenderer;
};
