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

LevelGenerator::LevelGenerator(EngineCore& engine, glm::vec2 levelSize, float earthPercentage) : engine(engine), levelSize(levelSize), earthPercentage(earthPercentage) {
	srand((unsigned)time(0));
}

void LevelGenerator::generateLevel() {
	auto gameObject = ObjectManager::GetInstance()->CreateGameObject("World");
	auto world_comp = ObjectManager::GetInstance()->CreateComponent<WorldComponent>(gameObject.get());

	addTerrain(world_comp.get());

	auto number = rand() % 3 + 3; // TODO: add clever number of islands 

	std::cout << "Number of island: " << number << std::endl;
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
	auto yOffset = levelSize.y * earthPercentage;
	auto yDeviation = yOffset * 0.8;
	std::vector<b2Vec2> result;
	std::vector<int> xPoints;

	int beginGenerationPointX = std::floor((emptyTerrainRatio / 2) * levelSize.x);
	int endGenerationPointX = std::floor((1 - emptyTerrainRatio / 2) * levelSize.x);

	for (int i = beginGenerationPointX; i < endGenerationPointX; i+=16) {
		xPoints.emplace_back(i);
	}

	TerrainUtils tu;
	
	result = tu.combineNoise(xPoints, tu.generateNoise(xPoints, 256, 128, 3, 2));

	tu.reshapeEdges(result);

	result.emplace_back(b2Vec2(levelSize.x - 1, 0));
	result.emplace_back(b2Vec2(beginGenerationPointX, 0));

	return result;
}

void LevelGenerator::addIslands(WorldComponent* world_comp, int amount) {
	std::vector<b2Vec2> islandPositions = createIslandPositions(world_comp, amount);
	std::vector<int> islandDimensions = createIslandDimensions(amount);

	for (int i = 0; i < amount; i++) {
		addIsland(world_comp, islandDimensions[i], islandPositions[i]);
	}	
}

std::vector<b2Vec2>  LevelGenerator::createIslandPositions(WorldComponent* world_comp, int number) {
	auto start_y = levelSize.y * earthPercentage;
	auto VERTICAL_DIVISION = 3;
	auto HORIZONTAL_DIVISION = 2;
	auto unit_x = levelSize.x / VERTICAL_DIVISION;
	auto offset_x = unit_x / 2;
	auto unit_y = (levelSize.y - start_y) / HORIZONTAL_DIVISION;
	auto offset_y =  unit_y / 2;
	//auto noise_x = 0;
	//auto noise_y = 0;
	//auto noise_scaler = 10;

	std::vector<b2Vec2> res;
	for (int i = 0; i < number; i++) {
		//noise_x = rand() % noise_scaler;
		//noise_y = rand() % noise_scaler;
		b2Vec2 new_pos = { static_cast<float32> (rand() % VERTICAL_DIVISION * unit_x + offset_x), static_cast<float32> (rand() % HORIZONTAL_DIVISION * unit_y + offset_y + start_y) };
		if (std::find(res.begin(), res.end(), new_pos) != res.end()) {
			/* res contains already that position --> avoiding islands on same position */
			i--;
		}
		else {
			res.push_back(new_pos/* + b2Vec2(noise_x, noise_y)*/);
		}
	}
	return res;
}

void LevelGenerator::addIsland(WorldComponent* world_comp, int size, b2Vec2 position) {
	auto points = createIslandPoints(size, position);
	world_comp->addRing(std::move(points));
}

std::vector<int> LevelGenerator::createIslandDimensions(int number) {
	auto SIZES = 3;
	std::vector<int> res;
	for (int i = 0; i < number; i++) {
		res.push_back(rand() % SIZES);
	}
	return res;
}

std::vector<b2Vec2> LevelGenerator::createIslandPoints(int size, b2Vec2 position) {
	// creating the vector of points of the island
	auto angle = 10.f;
	auto X_DIM = levelSize.x / 40 * (size+1);
	auto Y_DIM = levelSize.y / 120 * (size+1);
	float noise_y;
	std::vector<b2Vec2> result;

	for (int i = 0; i < 360/angle; i++) {
		noise_y = rand() % 20;
		

		if (angle * i > 90 && angle * i < 270)
			noise_y = -noise_y;

		result.push_back({ position.x + X_DIM*cos(glm::radians(angle*i)),
			position.y + Y_DIM*sin(glm::radians(angle*i)) + noise_y});
	}
	
	result.push_back(result.at(0));
	return result;
}

void LevelGenerator::addPortals(int couples) {
	
	auto blueSprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas("portal_blue_yellow.png", "portals");
	auto redSprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas("portal_yellow_blue.png", "portals");
	//building a couple of Portals every time
	for (int i = 0; i < couples; i++) {
		
		auto portal1 = ObjectManager::GetInstance()->CreateGameObject("Portal_" + std::to_string(i) + "_a");
		auto port1_comp = ObjectManager::GetInstance()->CreateComponent<PortalComponent>(portal1.get());
		

		auto portal2 = ObjectManager::GetInstance()->CreateGameObject("Portal_" + std::to_string(i) + "_b");
		auto port2_comp = ObjectManager::GetInstance()->CreateComponent<PortalComponent>(portal2.get());
		

		//set position of the gameObjects //TODO: find a better way to find where locate portals
		auto randX = [](){ return (rand() % 1800) + 100;};
		auto randY = [&](){ return (rand() % static_cast<int>(levelSize.y * (1-earthPercentage)) + levelSize.y * earthPercentage);};

		portal1->setPosition({ randX(), randY() });
		portal2->setPosition({ randX(), randY() });

		//initializing circles for physics
		port1_comp->initCircle(b2_staticBody, blueSprite.getSpriteSize().x / 4, portal1->getPosition(), 0.0f);
		port2_comp->initCircle(b2_staticBody, redSprite.getSpriteSize().x / 4, portal2->getPosition(), 0.0f);

		auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(portal1.get());
		spriteComp->setSprite(blueSprite);
		auto spriteComp1 = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(portal2.get());
		spriteComp1->setSprite(redSprite);

		//connecting the couple
		port1_comp->setOtherPortal(portal2);
		port2_comp->setOtherPortal(portal1);
	}
}