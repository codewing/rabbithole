//
// Created by codewing on 29.11.18.
//

#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <vector>

class IInteractable {

public:
    IInteractable();
    virtual ~IInteractable();

    virtual void onCollisionStart(IInteractable* interactable) = 0;  // Callback from physics engine when collision start is detected. Override when needed.
    virtual void onCollisionEnd(IInteractable* interactable) = 0;    // Callback from physics engine when collision end is detected. Override when needed.

    virtual void setPosition(glm::vec2 newPosition) = 0;
    virtual void setRotation(float newAngle) = 0;

    bool isSensor();
    void setSensor(bool enabled);

    void initCircle(b2BodyType type, float radius, glm::vec2 center, float density);
    void initBox(b2BodyType type, glm::vec2 size, glm::vec2 center, float density);
    void initChain(b2BodyType type, std::vector<b2Vec2> points, glm::vec2 position, float density);

    void addForce(glm::vec2 force);     // Force gradually affects the velocity over time
    void addImpulse(glm::vec2 impulse);   // Instantly affects velocity

    void setLinearVelocity(glm::vec2 velocity);
    glm::vec2 getLinearVelocity();

    void teleport(glm::vec2 newPosition, float newAngle);

protected:

    b2Shape* shape = nullptr;
    b2Body* body = nullptr;
    b2Shape::Type shapeType;
    b2Fixture* fixture = nullptr;
    b2BodyType rbType;
    b2World * world = nullptr;

    friend class ObjectManager;
    friend class PhysicsSystem;
};

