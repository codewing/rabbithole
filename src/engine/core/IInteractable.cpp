//
// Created by codewing on 29.11.18.
//

#include "IInteractable.hpp"

#include "ObjectManager.hpp"

IInteractable::IInteractable() {
    world = ObjectManager::GetInstance()->GetPhysicsWorld();
}

bool IInteractable::isSensor() {
    return fixture->IsSensor();
}

void IInteractable::setSensor(bool enabled) {
    fixture->SetSensor(enabled);
}

void IInteractable::addImpulse(glm::vec2 impulse) {
    b2Vec2 iForceV{impulse.x,impulse.y};
    body->ApplyLinearImpulse(iForceV, body->GetWorldCenter(), true);
}

void IInteractable::addForce(glm::vec2 force) {
    b2Vec2 forceV{force.x,force.y};
    body->ApplyForce(forceV,body->GetWorldCenter(),true);
}

glm::vec2 IInteractable::getLinearVelocity() {
    b2Vec2 v = body->GetLinearVelocity();
    return {v.x,v.y};
}

void IInteractable::setLinearVelocity(glm::vec2 velocity) {
    b2Vec2 v{velocity.x, velocity.y};
    if (velocity != glm::vec2(0,0)){
        body->SetAwake(true);
    }
    body->SetLinearVelocity(v);
}

void IInteractable::initCircle(b2BodyType type, float radius, glm::vec2 center, float density) {
    assert(body == nullptr);
    // do init
    shapeType = b2Shape::Type::e_circle;
    b2BodyDef bd;
    bd.type = type;
    rbType = type;
    bd.position = b2Vec2(center.x/PhysicsSystem::PHYSICS_SCALE, center.y/PhysicsSystem::PHYSICS_SCALE);
    body = world->CreateBody(&bd);
    shape = new b2CircleShape();
    shape->m_radius = radius / PhysicsSystem::PHYSICS_SCALE;
    b2FixtureDef fxD;
    fxD.shape = shape;
    fxD.density = density;
    fixture = body->CreateFixture(&fxD);

    ObjectManager::GetInstance()->EnablePhysics(this);
}

void IInteractable::initBox(b2BodyType type, glm::vec2 size, glm::vec2 center, float density) {
    assert(body == nullptr);
    // do init
    shapeType = b2Shape::Type::e_polygon;
    b2BodyDef bd;
    bd.type = type;
    rbType = type;
    bd.position = b2Vec2(center.x / PhysicsSystem::PHYSICS_SCALE, center.y / PhysicsSystem::PHYSICS_SCALE);
    body = world->CreateBody(&bd);
    auto polyShape = new b2PolygonShape();
    polyShape->SetAsBox(size.x / PhysicsSystem::PHYSICS_SCALE, size.y / PhysicsSystem::PHYSICS_SCALE, {0,0}, 0);
    shape = polyShape;
    b2FixtureDef fxD;
    fxD.shape = shape;
    fxD.density = density;
    fixture = body->CreateFixture(&fxD);

    ObjectManager::GetInstance()->EnablePhysics(this);
}

IInteractable::~IInteractable() {
    ObjectManager::GetInstance()->DisablePhysics(this);

    delete shape;
    if (body != nullptr && fixture!= nullptr ) {
        body->DestroyFixture(fixture);
        fixture = nullptr;
    }
    if (world != nullptr && body != nullptr ) {
        world->DestroyBody(body);
        body = nullptr;
    }
}