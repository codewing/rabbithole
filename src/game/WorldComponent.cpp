//
// Created by Morten Nobel-Jørgensen on 11/4/17.
//

#include <Box2D/Box2D.h>
#include <iostream>
#include <glm/ext.hpp>
#include "WorldComponent.hpp"
#include "PlatformerGame.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"

WorldComponent::WorldComponent(GameObject *gameObject) : Component(gameObject) {
    auto game = PlatformerGame::instance;
    physicsScale = game->physicsScale;
}

void WorldComponent::initTerrain(std::shared_ptr<sre::SpriteAtlas> spriteAtlas, std::vector<b2Vec2> positions, int size, int startSpriteId, int height) {
	this->kinematic = false; // terrain cannot be moved
	auto game = PlatformerGame::instance;

	// without SpriteComponent
	// auto spriteComponent = gameObject->addComponent<SpriteComponent>();
	// auto sprite = spriteAtlas->get(std::to_string(startSpriteId + 30) + ".png");
	// spriteComponent->setSprite(sprite);

	gameObject->setPosition(pos);

}

void WorldComponent::initIsland(std::shared_ptr<sre::SpriteAtlas> spriteAtlas, std::vector<b2Vec2> points, int size, b2Vec2 position, float density) {
	this->kinematic = false; // islands cannot be moved
	auto game = PlatformerGame::instance;

	// without SpriteComponent
	// auto spriteComponent = gameObject->addComponent<SpriteComponent>();
	// auto sprite = spriteAtlas->get(std::to_string(startSpriteId + 30) + ".png");
	
	glm::vec2 new_pos = { position.x, position.y };
	gameObject->setPosition(new_pos);
	this->pos = new_pos;

	// spriteComponent->setSprite(sprite);
	
	std::vector<glm::vec2> scaled_points;
	for (int i = 0; i < points.size(); i++) {
		scaled_points.push_back( {points[i].x / physicsScale, points[i].y / physicsScale} );
	}

}


void WorldComponent::moveTo(glm::vec2 tilePos) {
    assert(kinematic);
    glm::vec2 offset{Level::tileSize/2,Level::tileSize/2};
    pos = offset + glm::vec2{tilePos.x*Level::tileSize,tilePos.y*Level::tileSize};
    this->pos = pos;

    gameObject->setPosition(pos);

    glm::vec2 physPos = pos;
    physPos.x += (width-1)*0.5f*Level::tileSize;


    for (int i=0;i<tiles.size();i++){
        pos.x += Level::tileSize;
        tiles[i]->setPosition(pos);
    }
}

glm::vec2 WorldComponent::getPosition() {
    return pos;
}

void WorldComponent::update(float deltaTime) {
    if (kinematic){
        glm::vec2 physPos = pos;
        physPos.x += (width-1)*0.5f*Level::tileSize;
    }
}

float WorldComponent::GetPercOfTerrain() {
	return percOfTerrain;
}

std::vector<std::vector<b2Vec2>> WorldComponent::getRings() {
	return listOfRings;
}

void WorldComponent::addRing(std::vector<b2Vec2> ring) {
	listOfRings.push_back(ring);
}