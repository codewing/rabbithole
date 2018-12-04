//
// Created by Morten Nobel-Jørgensen on 11/3/17.
//

#include "LevelGenerator.hpp"
#include "WorldComponent.hpp"
#include <boost/geometry/geometry.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include <poly2tri/poly2tri.h>
#include "../engine/core/ObjectManager.hpp"

LevelGenerator::LevelGenerator(glm::vec2 levelSize, float earthPercentage) : levelSize(levelSize), earthPercentage(earthPercentage) {
	srand((unsigned)time(0));
}

void LevelGenerator::generateLevel() {
	auto gameObject = ObjectManager::GetInstance()->CreateGameObject("World");
	auto world_comp = ObjectManager::GetInstance()->CreateComponent<WorldComponent>(gameObject.get());

	addTerrain(world_comp.get());

	auto number = rand() % 3 + 3; // TODO: add clever number of islands 

	std::cout << "Number of island: " << number << std::endl;
	addIslands(world_comp.get(), number);

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

	for (int i = 0; i < levelSize.x; i++) {
		xPoints.emplace_back(i);
	}

	TerrainUtils tu;
	
	result = tu.combineNoise(xPoints, tu.generateNoise(xPoints, 128, 128, 5, 2));
	result.emplace(result.begin(), b2Vec2(0, 0));
	result.emplace_back(b2Vec2(levelSize.x - 1, 0));
	result.emplace_back(b2Vec2(0, 0));

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

float LevelGenerator::evaluateTerrainFunction(float x) {
	return -(x * (x-0.3f) * (x-0.6f) * (x-1)) * 25;
}
