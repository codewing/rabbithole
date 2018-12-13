//
// Created by codewing on 29.11.18.
//

#pragma once

#include "../engine/core/IInteractable.hpp"
#include <Box2D/Box2D.h>

class WorldComponent;

class TerrainInteractable : public IInteractable{
public:
    TerrainInteractable(WorldComponent *worldComponent, std::vector<b2Vec2> terrainData);

    void onCollisionStart(IInteractable *interactable) override;

    void onCollisionEnd(IInteractable *interactable) override;

    void setPosition(glm::vec2 newPosition) override;

    void setRotation(float newAngle) override;

    glm::vec2 getPosition() override;

    std::vector<b2Vec2>& getTerrainData();

private:

    WorldComponent* worldComponent;

    std::vector<b2Vec2> terrainData;
    bool isBeingUpdated = false;

};

