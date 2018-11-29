#pragma once

#include <memory>
#include <vector>
#include <sre/SpriteAtlas.hpp>
#include <boost/geometry/geometry.hpp>
#include <Box2D/Common/b2Math.h>

class PlatformerGame;
class GameObject;
class WorldComponent;

enum class TileCollider {
    Block,
    BlockHalf,
    Incline,
    Decline
};

class Level {
public:
    static std::shared_ptr<Level> createDefaultLevel(glm::vec2 levelSize);

    void generateLevel();
	void addTerrain(WorldComponent* world_comp);
	void addIslands(WorldComponent* world_comp, int number);
	void addIsland(WorldComponent* world_comp, int size, b2Vec2 position);
	std::vector<b2Vec2>  createIslandPositions(WorldComponent* world_comp, int number);
	std::vector<int> createIslandDimensions(int number);
	std::vector<b2Vec2> createTerrain(WorldComponent* world_comp);
	std::vector<b2Vec2> createIslandPoints(int size, b2Vec2 position);



    static constexpr float tileSize = 21;
	static constexpr int terrainResolution = 800;

    Level(glm::vec2 levelSize, float earthPercentage);


private:
	PlatformerGame* game;

    glm::vec2 levelSize;
    float earthPercentage;
};