#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IRenderable.hpp"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include "RingInteractable.hpp"
#include <sre/Mesh.hpp>
#include "TerrainUtils.hpp"
#include "../engine/core/IUpdatable.hpp"

class GameObject;

class WorldComponent : public Component, public IRenderable, public IUpdatable {
public:
    explicit WorldComponent(GameObject* gameObject);

    void onRender(sre::RenderPass &renderPass) override;

	void onUpdate(float deltaTime) override;

	std::vector<std::shared_ptr<RingInteractable>>& getRings();
	void addRing(std::vector<b2Vec2> ring);

	void updateMeshes();

	void registerRemoveShapeFromRing(RingInteractable* ringToModify, polygon_t shapeToRemove);

private:

	std::vector<std::shared_ptr<RingInteractable>> rings;
	std::vector<std::pair<RingInteractable*, polygon_t>> ringsToUpdate;
	std::vector<std::shared_ptr<sre::Mesh>> worldMeshes;

	std::shared_ptr<sre::Material> worldMaterial;
    std::shared_ptr<sre::Mesh> backgroundMesh;

	std::shared_ptr<sre::Material> backgroundMaterial;
	TerrainUtils terrainUtils;

	void initializeBackground();

	void removeShapeFromRing(RingInteractable* ringToModify, polygon_t shapeToRemove);
};