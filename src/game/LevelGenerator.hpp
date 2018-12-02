#pragma once

#include <memory>
#include <vector>
#include <sre/SpriteAtlas.hpp>
#include <boost/geometry/geometry.hpp>
#include <Box2D/Common/b2Math.h>

class GameObject;
class WorldComponent;

class LevelGenerator {
public:
    void generateLevel();
	void addTerrain(WorldComponent* world_comp);
	void addIslands(WorldComponent* world_comp, int number);
	void addIsland(WorldComponent* world_comp, int size, b2Vec2 position);
	std::vector<b2Vec2>  createIslandPositions(WorldComponent* world_comp, int number);
	std::vector<int> createIslandDimensions(int number);
	std::vector<b2Vec2> createTerrain(WorldComponent* world_comp);
	std::vector<b2Vec2> createIslandPoints(int size, b2Vec2 position);

	static constexpr int sampleDistancePX = 20;

    LevelGenerator(glm::vec2 levelSize, float earthPercentage);

private:
    glm::vec2 levelSize;
    float earthPercentage;

	float evaluateTerrainFunction(float x);
};