//
// Created by codewing on 28.11.18.
//

#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IUpdatable.hpp"
#include "../engine/core/IInputable.hpp"
#include "../engine/component/PhysicsComponent.hpp"

class MovementComponent : public Component, public IUpdatable, public IInputable {

public:
    explicit MovementComponent(GameObject *gameObject);

    void onUpdate(float deltaTime) override;
    bool onKeyEvent(SDL_Event &event) override;
	void setGrounded(bool value);
    bool onControllerEvent(SDL_Event &event) override;

    void setupControllerInput(int gamepadID);

    virtual ~MovementComponent();

private:

    std::shared_ptr<PhysicsComponent> physicsComponent = nullptr;

    float moveUp = 0;
    float moveRight = 0;
    bool jump = false;
	bool isGrounded = false;

    int gamepadID = -1;
    SDL_GameController* controllerHandle = nullptr;
    static constexpr float axisValueMax = 32768;
    static constexpr float controllerDeadzone = 0.02;
};
