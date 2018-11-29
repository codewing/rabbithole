#pragma once

#include "../engine/core/Component.hpp"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <Box2D/Common/b2Math.h>

class GameObject;

class WorldComponent : public Component {
public:
    explicit WorldComponent(GameObject* gameObject);

    glm::vec2 getPosition();
	float GetPercOfTerrain();
	std::vector<std::vector<b2Vec2>> getRings();
	void addRing(std::vector<b2Vec2> ring);

private:
	std::vector<std::vector<b2Vec2>> listOfRings;
	float percOfTerrain = 0.6;
    int width;
};