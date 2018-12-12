#pragma once

#include "../core/Component.hpp"
#include "../core/PhysicsSystem.hpp"
#include "../core/IInteractable.hpp"

class PhysicsComponent : public Component, public IInteractable {
public:
    explicit PhysicsComponent(GameObject *gameObject);
    virtual ~PhysicsComponent();

    void onCollisionStart(IInteractable* interactable) override;  // Callback from physics engine when collision start is detected. Override when needed.
    void onCollisionEnd(IInteractable* interactable) override;    // Callback from physics engine when collision end is detected. Override when needed.

    void setPosition(glm::vec2 newPosition) override;

    glm::vec2 getPosition() override;

    void setRotation(float newAngle) override;
};

