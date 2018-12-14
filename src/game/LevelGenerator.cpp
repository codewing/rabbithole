#include "LevelGenerator.hpp"
#include "PortalComponent.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include "WorldComponent.hpp"
#include <boost/geometry/geometry.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include <poly2tri/poly2tri.h>
#include "../engine/core/ObjectManager.hpp"
#include "../engine/debug/Log.hpp"

LevelGenerator::LevelGenerator(glm::vec2 levelSize, float earthPercentage) : levelSize(levelSize), earthPercentage(earthPercentage) {
    auto seed = (unsigned)time(0);
    LOG_GAME_INFO("Seeded with: " + std::to_string(seed));
    srand(seed);
}

void LevelGenerator::generateLevel() {
    auto gameObject = ObjectManager::GetInstance()->CreateGameObject("World");
    auto world_comp = ObjectManager::GetInstance()->CreateComponent<WorldComponent>(gameObject.get());

    addTerrain(world_comp.get());

    auto number = rand() % 3 + 3;
    LOG_GAME_INFO("Number of island: " + std::to_string(number));
    addIslands(world_comp.get(), number);

    addPortals(2);
    // Building the visual representation
    world_comp->updateMeshes();
}

void LevelGenerator::addTerrain(WorldComponent* world_comp) {

    std::vector<b2Vec2> points = createTerrain(world_comp);
    world_comp->addRing(std::move(points));
}

// generating the list of positions of the terrain
std::vector<b2Vec2> LevelGenerator::createTerrain(WorldComponent* world_comp) {
    std::vector<int> xPoints;

    int beginGenerationPointX = static_cast<int>(std::floor((emptyTerrainRatio / 2) * levelSize.x));
    int endGenerationPointX = static_cast<int>(std::floor((1 - emptyTerrainRatio / 2) * levelSize.x));

    for (int i = beginGenerationPointX; i <= endGenerationPointX; i+=16) {
        xPoints.emplace_back(i);
    }

    std::vector<b2Vec2> result = TerrainUtils::combineNoise(xPoints, TerrainUtils::generateNoise(xPoints, 256, 128, 3, 4));
    TerrainUtils::reshapeEdges(result);

    result.emplace_back(b2Vec2(beginGenerationPointX, 0));

    return result;
}

void LevelGenerator::addIslands(WorldComponent* world_comp, int amount) {
    std::vector<b2Vec2> islandPositions = createIslandCenterPoints(amount);
    std::vector<int> islandDimensions = createRandomIslandSizes(amount);

    for (int i = 0; i < amount; i++) {
        addIsland(world_comp, islandDimensions[i], islandPositions[i]);
    }
}

std::vector<b2Vec2>  LevelGenerator::createIslandCenterPoints(int number) {
    auto start_y = levelSize.y * earthPercentage;

    b2Vec2 ringCentre = { levelSize.x / 2, (levelSize.y + start_y) / 2 };
    float angle = 360.f / number;
    float X_DIM = (levelSize.x / 2) * 0.6f;
    float Y_DIM = ((levelSize.y + start_y) / 4) * 0.8f;
    float positionDelta = (static_cast<float>(rand()) / (RAND_MAX + 1)) * angle;

    std::vector<b2Vec2> result;

    for (int i = 0; i < 360 / angle; i++) {
        result.push_back({ ringCentre.x + X_DIM * cos(glm::radians(angle*i + positionDelta)),
                           ringCentre.y + Y_DIM * sin(glm::radians(angle*i + positionDelta))});
    }

    result.push_back(result.at(0));
    return result;
}

void LevelGenerator::addIsland(WorldComponent* world_comp, int size, b2Vec2 position) {
    auto points = createIslandPoints(size, position);
    world_comp->addRing(std::move(points));
}

std::vector<int> LevelGenerator::createRandomIslandSizes(int number) {
    auto SIZES = 2;
    std::vector<int> res;
    for (int i = 0; i < number; i++) {
        res.push_back(rand() % SIZES + 1);
    }
    return res;
}

std::vector<b2Vec2> LevelGenerator::createIslandPoints(int size, b2Vec2 islandCenter) {
    // creating the vector of points of the island
    auto angle = 10.f;
    auto X_DIM = levelSize.x / 24 * (size+1);
    auto Y_DIM = levelSize.y / 64 * (size+1);
    float noise_y;
    std::vector<b2Vec2> result;

    for (int i = 0; i < 360/angle; i++) {
        noise_y = rand() % 20;

        if (angle * i > 90 && angle * i < 270)
            noise_y = -noise_y;

        result.push_back({ islandCenter.x + X_DIM*cos(glm::radians(angle*i)),
                           islandCenter.y + Y_DIM*sin(glm::radians(angle*i)) + noise_y});
    }

    result.push_back(result.at(0));
    return result;
}

void LevelGenerator::addPortals(int couples) {

    std::vector<std::string> portals = {"portal_blue_yellow.png", "portal_yellow_blue.png", "portal_red_green.png", "portal_green_red.png"};

	//building a couple of Portals every time
	for (int i = 0; i < couples; i++) {
		
		auto portal1 = ObjectManager::GetInstance()->CreateGameObject("Portal_" + std::to_string(i) + "_a");
		auto port1_comp = ObjectManager::GetInstance()->CreateComponent<PortalComponent>(portal1.get());
		

		auto portal2 = ObjectManager::GetInstance()->CreateGameObject("Portal_" + std::to_string(i) + "_b");
		auto port2_comp = ObjectManager::GetInstance()->CreateComponent<PortalComponent>(portal2.get());
		

		//set position of the gameObjects //TODO: find a better way to find where locate portals
		auto randX = [](){ return (rand() % 1800) + 100;};
		auto randY = [&](){ return (rand() % static_cast<int>(levelSize.y * (1-earthPercentage)) + levelSize.y * earthPercentage);};

        portal1->setLocalPosition({randX(), randY()});
        portal2->setLocalPosition({randX(), randY()});

        auto sprite1 = ObjectManager::GetInstance()->GetTextureSystem().getSpriteFromAtlas(portals[2*i], "portals");
        auto sprite2 = ObjectManager::GetInstance()->GetTextureSystem().getSpriteFromAtlas(portals[2*i + 1], "portals");

		//initializing circles for physics
		port1_comp->initCircle(b2_staticBody, sprite1.getSpriteSize().x / 4.0f, portal1->getLocalPosition(), 0.0f);
		port2_comp->initCircle(b2_staticBody, sprite2.getSpriteSize().x / 4.0f, portal2->getLocalPosition(), 0.0f);

		port1_comp->setSensor(true);
		port2_comp->setSensor(true);

		auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(portal1.get());
		spriteComp->setSprite(sprite1);
		auto spriteComp1 = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(portal2.get());
		spriteComp1->setSprite(sprite2);

		//connecting the couple
		port1_comp->setOtherPortal(port2_comp.get());
		port2_comp->setOtherPortal(port1_comp.get());
	}
}