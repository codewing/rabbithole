//
// Created by codewing on 29.11.18.
//

#pragma once

#include "../engine/core/IInteractable.hpp"
#include "Level.hpp"

class RingInteractable : public IInteractable{
public:
    void onCollisionStart(IInteractable *interactable) override;

    void onCollisionEnd(IInteractable *interactable) override;

    void setPosition(glm::vec2 newPosition) override;

    void setRotation(float newAngle) override;

private:

    Level* level;

};

