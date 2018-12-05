#pragma once

#include <memory>
#include <vector>
#include <sre/SpriteAtlas.hpp>
#include <boost/geometry/geometry.hpp>
#include <Box2D/Common/b2Math.h>
#include "../engine/core/EngineCore.hpp"

class GameObject;
class WorldComponent;

class LevelGenerator {
public:
    void generateLevel();
	void addTerrain(WorldComponent* world_comp);
	void addIslands(WorldComponent* world_comp, int number);
	void addIsland(WorldComponent* world_comp, int size, b2Vec2 position);
	void addPortals(int couples);
	std::vector<b2Vec2>  createIslandPositions(WorldComponent* world_comp, int number);
	std::vector<int> createIslandDimensions(int number);
	std::vector<b2Vec2> createTerrain(WorldComponent* world_comp);
	std::vector<b2Vec2> createIslandPoints(int size, b2Vec2 position);

	static constexpr float emptyTerrainRatio = 0.25f;
	static constexpr float roundTerrainRatio = 0.25f;
	static constexpr float straightTerrainRatio = 0.5f;

    LevelGenerator(EngineCore& engine, glm::vec2 levelSize, float earthPercentage);

private:
	glm::vec2 levelSize;
    float earthPercentage;
	EngineCore& engine;
};