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
	LevelGenerator(glm::vec2 levelSize, float earthPercentage);

	std::shared_ptr<GameObject> generateLevel();
	void addTerrain(WorldComponent* world_comp);
	void addIslandsSpawnPointsAndPortals(WorldComponent *world_comp, int number);
	void addIsland(WorldComponent* world_comp, int size, b2Vec2 position);
	void addPortals(int couples, const std::vector<glm::vec2>& portalPositions);

	std::vector<b2Vec2> createIslandCenterPoints(int number);
	std::vector<int> createRandomIslandSizes(int number);
	std::vector<b2Vec2> createTerrain(WorldComponent* world_comp);
	std::vector<b2Vec2> createIslandPoints(int size, b2Vec2 islandCenter);
	std::vector<std::pair<glm::vec2, glm::vec2>> createPossibleSpawnPoints(const std::vector<b2Vec2> &islandPositions, const std::vector<int>& islandDimensions);

	std::vector<glm::vec2>& getSpawnPoints();

	static constexpr float emptyTerrainRatio = 0.125f;
	static constexpr float roundTerrainRatio = 0.375f;

private:
	glm::vec2 levelSize;
    float earthPercentage;

    std::vector<glm::vec2> spawnPoints;
};