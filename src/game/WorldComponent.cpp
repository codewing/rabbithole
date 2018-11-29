//
// Created by Morten Nobel-Jørgensen on 11/4/17.
//

#include "WorldComponent.hpp"

#include <Box2D/Box2D.h>
#include <iostream>
#include <glm/ext.hpp>
#include "../engine/core/GameObject.hpp"

WorldComponent::WorldComponent(GameObject* gameObject) : Component(gameObject, 0) {}

glm::vec2 WorldComponent::getPosition() {
    return gameObject->getPosition();
}

float WorldComponent::GetPercOfTerrain() {
	return percOfTerrain;
}

std::vector<std::vector<b2Vec2>> WorldComponent::getRings() {
	return listOfRings;
}

void WorldComponent::addRing(std::vector<b2Vec2> ring) {
	listOfRings.push_back(ring);
}