#pragma once

#include "../engine/core/Component.hpp"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include "RingInteractable.hpp"

class GameObject;

class WorldComponent : public Component {
public:
    explicit WorldComponent(GameObject* gameObject);

	std::vector<RingInteractable>& getRings();
	void addRing(std::vector<b2Vec2> ring);

private:
	std::vector<RingInteractable> rings;
};