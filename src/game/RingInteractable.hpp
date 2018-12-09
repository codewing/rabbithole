//
// Created by codewing on 29.11.18.
//

#pragma once

#include "../engine/core/IInteractable.hpp"
#include <Box2D/Box2D.h>

class WorldComponent;

class RingInteractable : public IInteractable{
public:
    RingInteractable(WorldComponent *worldComponent, std::vector<b2Vec2> ringData);

    void onCollisionStart(IInteractable *interactable) override;

    void onCollisionEnd(IInteractable *interactable) override;

    void setPosition(glm::vec2 newPosition) override;

    void setRotation(float newAngle) override;

    std::vector<b2Vec2> const getRingData();

private:

    WorldComponent* worldComponent;

    std::vector<b2Vec2> ringData;

};

