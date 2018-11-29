//
// Created by Morten Nobel-Jørgensen on 11/3/17.
//

#include "Level.hpp"
#include "WorldComponent.hpp"
#include <boost/geometry/geometry.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include <poly2tri/poly2tri.h>
#include "../engine/core/ObjectManager.hpp"

Level::Level(glm::vec2 levelSize) : levelSize(levelSize) {
	srand((unsigned)time(0));
}

std::shared_ptr<Level> Level::createDefaultLevel(glm::vec2 levelSize) {
    std::shared_ptr<Level> res = std::shared_ptr<Level>(new Level(levelSize));

    return res;
}

void Level::generateLevel() {
	auto gameObject = ObjectManager::GetInstance()->CreateGameObject("World");
	auto world_comp = ObjectManager::GetInstance()->CreateComponent<WorldComponent>(gameObject.get());

	addTerrain(world_comp.get());

	auto number = rand() % 5 + 1; // TODO: add clever number of islands (right now is [1, 2, 3])

	std::cout << "Number of island: " << number << std::endl;
	addIslands(world_comp.get(), number);

	for (auto ring : world_comp->getRings()) {
		std::cout << "First x component of 1st element of the ring " << ring.at(0).x << std::endl;
		auto phys_comp = ObjectManager::GetInstance()->CreateComponent<PhysicsComponent>(gameObject.get());
		phys_comp->initChain(b2BodyType::b2_staticBody, ring, gameObject->getPosition(), 1);
	}
}

void Level::addTerrain(WorldComponent* world_comp) {
	
	std::vector<b2Vec2> points = createTerrain(world_comp);
	world_comp->addRing(points);
}

// generating the list of positions of the terrain
std::vector<b2Vec2> Level::createTerrain(WorldComponent* world_comp) {
	auto percentage_of_terrain = world_comp->GetPercOfTerrain();
	auto start_y = levelSize.x * percentage_of_terrain * 0.6;
	std::vector<b2Vec2> result;
	float x, y;
	float a, phi, omega_lf;
	float b, theta, omega_mf;
	float c, xi, omega_hf;
	float delta = 1;

	// Generating sampling parameters for low frequency function
	a = 40;
	phi = rand() % 360;
	omega_lf = 1;

	// Generating sampling parameters for medium frequency function
	b = 20;
	theta = rand() % 360;
	omega_mf = 2.5;

	// Generating sampling parameters for high frequency function
	c = 10;
	xi = rand() % 360;
	omega_hf = 9;

	result.push_back(b2Vec2(0, 0));
	for (int i = 0; i < terrainResolution; i++) {
		x = i * delta;
		y = start_y;
		y += a * sin(glm::radians(omega_lf * x + phi));
		y += b * sin(glm::radians(omega_mf * x + theta));
		y += c * sin(glm::radians(omega_hf * x + xi));
		result.push_back(b2Vec2(x, y));
	}
	result.push_back(b2Vec2(int(terrainResolution * delta), 0));
	result.push_back(b2Vec2(0, 0));
	
	return result;
}

void Level::addIslands(WorldComponent* world_comp, int amount) {
	std::vector<b2Vec2> islandPositions = createIslandPositions(world_comp, amount);
	std::vector<int> islandDimensions = createIslandDimensions(amount);

	for (int i = 0; i < amount; i++) {
		addIsland(world_comp, islandDimensions[i], islandPositions[i]);
	}	
}

std::vector<b2Vec2>  Level::createIslandPositions(WorldComponent* world_comp, int number) {
	auto percentage_of_terrain = world_comp->GetPercOfTerrain();
	auto start_y = levelSize.y * percentage_of_terrain;
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

void Level::addIsland(WorldComponent* world_comp, int size, b2Vec2 position) {
	auto points = createIslandPoints(size, position);
	world_comp->addRing(points);
}

std::vector<int> Level::createIslandDimensions(int number) {
	auto SIZES = 3;
	std::vector<int> res;
	for (int i = 0; i < number; i++) {
		res.push_back(rand() % SIZES);
	}
	return res;
}

std::vector<b2Vec2> Level::createIslandPoints(int size, b2Vec2 position) {
	// creating the vector of points of the island
	auto angle = 10.f;
	auto X_DIM = 40 * (size+1);
	auto Y_DIM = 15 * (size+1);
	float noise_y;
	std::vector<b2Vec2> result;

	for (int i = 0; i < 360/angle; i++) {
		noise_y = rand() % 5;
		

		if (angle * i > 90 && angle * i < 270)
			noise_y = -noise_y;

		result.push_back({ position.x + X_DIM*cos(glm::radians(angle*i)),
			position.y + Y_DIM*sin(glm::radians(angle*i)) + noise_y});
	}
	result.push_back(result.at(0));
	return result;
}
