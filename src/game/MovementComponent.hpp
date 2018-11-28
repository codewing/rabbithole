//
// Created by codewing on 28.11.18.
//

#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IUpdatable.hpp"
#include "../engine/core/IInputable.hpp"

class MovementComponent : public Component, public IUpdatable, public IInputable {

public:
    explicit MovementComponent(GameObject *gameObject);

    void onUpdate(float deltaTime) override;

    bool onKeyEvent(SDL_Event &event) override;
};

