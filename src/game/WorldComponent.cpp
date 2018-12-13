#include "WorldComponent.hpp"

#include <Box2D/Box2D.h>
#include <iostream>
#include <glm/ext.hpp>
#include "../engine/core/GameObject.hpp"
#include <sre/Shader.hpp>
#include <sre/Texture.hpp>


WorldComponent::WorldComponent(GameObject* gameObject) : Component(gameObject, ComponentFlag::RENDERABLE | ComponentFlag::UPDATE) {
	worldMaterial = sre::Shader::getUnlit()->createMaterial();
	auto texture = sre::Texture::create().withFile("assets/images/scene/terrain_green.png")
			.withGenerateMipmaps(false)
			.withFilterSampling(true)
			.build();
	worldMaterial->setTexture(texture);

	initializeBackground();
}

void WorldComponent::addRing(std::vector<b2Vec2> ring) {
    std::shared_ptr<RingInteractable> physicsRing = std::make_shared<RingInteractable>(this, ring);
	rings.push_back(physicsRing);
}

std::vector<std::shared_ptr<RingInteractable>> &WorldComponent::getRings() {
	return rings;
}

void WorldComponent::updateMeshes() {
	worldMeshes.clear();

	for(auto& ring : rings) {
		auto mesh = terrainUtils.generateMesh(ring->getRingData());
		worldMeshes.emplace_back(mesh);
	}
}

void WorldComponent::onRender(sre::RenderPass &renderPass) {
	renderPass.draw(backgroundMesh, glm::mat4(1), backgroundMaterial);
	for(auto& mesh : worldMeshes) {
		renderPass.draw(mesh, glm::mat4(1), worldMaterial);
	}
}

void WorldComponent::initializeBackground() {
	std::vector<glm::vec3> backgroundPoints = {
			glm::vec3{0,0,-0.5}, glm::vec3{2048, 2048, -0.5}, glm::vec3{0, 2048.0, -0.5},
			glm::vec3{0,0,-0.5}, glm::vec3{2048, 0, -0.5}, glm::vec3{2048, 2048.0, -0.5},
	};

	std::vector<glm::vec4> backgroundUVs = {
			glm::vec4{0,0,0,1}, glm::vec4{1, 1, 0,1}, glm::vec4{0, 1, 0,1},
			glm::vec4{0,0,0,1}, glm::vec4{1, 0, 0,1}, glm::vec4{1, 1, 0,1},
	};

	backgroundMesh = sre::Mesh::create()
			.withPositions(backgroundPoints)
			.withUVs(backgroundUVs)
			.build();

	backgroundMaterial = sre::Shader::getUnlit()->createMaterial();
	auto texture = sre::Texture::create().withFile("assets/images/scene/background_light.png")
			.withGenerateMipmaps(false)
			.withFilterSampling(true)
			.build();
	backgroundMaterial->setTexture(texture);
}

void WorldComponent::removeShapeFromRing(RingInteractable* ringToModify, ring_t shapeToRemove) {
	std::vector<b2Vec2> previousRingData = ringToModify->getRingData();

	// remove old ring from the list
	auto iter(std::remove_if(rings.begin(), rings.end(), [ringToModify](std::shared_ptr<RingInteractable> currentRing) {return currentRing.get() == ringToModify;}));
	rings.erase(iter);

	// build a boost ring
	auto boostRing = terrainUtils.toRing(previousRingData);
	ring_collection_t newRings;
	TerrainUtils::subtract(boostRing, shapeToRemove, newRings);
    TerrainUtils::simplify(newRings);

	// convert and add the rings
	auto newB2Rings = terrainUtils.toWorldComponentStruct(newRings);
	for(auto& b2Ring : newB2Rings) {
		if(b2Ring.size() > 2) {
			addRing(b2Ring);
		}
	}
}

void WorldComponent::onUpdate(float deltaTime) {
	if(!ringsToUpdate.empty()) {
		for(auto& ringToUpdate : ringsToUpdate) {
			removeShapeFromRing(ringToUpdate.first, ringToUpdate.second);
		}
		ringsToUpdate.clear();
		updateMeshes();
	}
}

void WorldComponent::registerRemoveShapeFromRing(RingInteractable *ringToModify, ring_t shapeToRemove) {
	ringsToUpdate.emplace_back(std::pair{ringToModify, shapeToRemove});
}
