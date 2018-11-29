#include "WorldComponent.hpp"

#include <Box2D/Box2D.h>
#include <iostream>
#include <glm/ext.hpp>
#include "../engine/core/GameObject.hpp"

WorldComponent::WorldComponent(GameObject* gameObject) : Component(gameObject, 0) {}

void WorldComponent::addRing(std::vector<b2Vec2> ring) {
	rings.push_back(RingInteractable{this, std::move(ring)});
}

std::vector<RingInteractable> &WorldComponent::getRings() {
	return rings;
}
