//
// Created by codewing on 08.11.18.
//

#ifndef SIMPLERENDERENGINEPROJECT_PHYSICS_H
#define SIMPLERENDERENGINEPROJECT_PHYSICS_H

#include "Box2D/Dynamics/b2World.h"

class Physics : public b2ContactListener {

public:

    Physics();

private:
    void initPhysics();

    b2World* world = nullptr;

};


#endif //SIMPLERENDERENGINEPROJECT_PHYSICS_H
