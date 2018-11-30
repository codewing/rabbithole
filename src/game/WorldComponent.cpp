#include "WorldComponent.hpp"

#include <Box2D/Box2D.h>
#include <iostream>
#include <glm/ext.hpp>
#include "../engine/core/GameObject.hpp"

WorldComponent::WorldComponent(GameObject* gameObject) : Component(gameObject, 0) {}

void WorldComponent::addRing(std::vector<b2Vec2> ring) {
    std::shared_ptr<RingInteractable> physicsRing = std::make_shared<RingInteractable>(this, std::move(ring));
	rings.push_back(std::move(physicsRing));
}

std::vector<std::shared_ptr<RingInteractable>> &WorldComponent::getRings() {
	return rings;
}
