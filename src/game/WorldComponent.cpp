#include "WorldComponent.hpp"

#include <Box2D/Box2D.h>
#include <iostream>
#include <glm/ext.hpp>
#include "../engine/core/GameObject.hpp"
#include <sre/Shader.hpp>


WorldComponent::WorldComponent(GameObject* gameObject) : Component(gameObject, ComponentFlag::RENDERABLE) {}

void WorldComponent::addRing(std::vector<b2Vec2> ring) {
    std::shared_ptr<RingInteractable> physicsRing = std::make_shared<RingInteractable>(this, std::move(ring));
	rings.push_back(std::move(physicsRing));
}

std::vector<std::shared_ptr<RingInteractable>> &WorldComponent::getRings() {
	return rings;
}

void WorldComponent::updateMeshes() {
	for(auto& ring : rings) {
		auto mesh = terrainUtils.generateMesh(ring->getRingData());
		worldMeshes.emplace_back(mesh);
	}
}

void WorldComponent::onRender(sre::RenderPass &renderPass) {
	std::shared_ptr<sre::Material> mat = sre::Shader::getUnlit()->createMaterial();
	mat->setColor(sre::Color(1, 0, 0, 1));

	for(auto& mesh : worldMeshes) {
		renderPass.draw(mesh, glm::mat4(1), mat);
	}
}
