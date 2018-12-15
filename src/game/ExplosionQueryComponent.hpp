//
// Created by codewing on 15.12.18.
//

#pragma once


#include <Box2D/Box2D.h>
#include "../engine/core/Component.hpp"

class ExplosionQueryComponent : public Component, public b2QueryCallback {
public:
    ExplosionQueryComponent(GameObject *gameObject);

    void explode(float explosionRadius, glm::vec2 center);

    bool ReportFixture(b2Fixture *fixture) override;

private:
    b2World* world;

    float radius;
    b2Vec2 explosionLocation;
};

