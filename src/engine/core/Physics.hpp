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

private:
    b2World* world = nullptr;

    std::map<b2Fixture*, PhysicsComponent*> physicsComponentLookup;

    void initPhysics();

    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
    void handleContact(b2Contact *contact, bool isBegin);

};
