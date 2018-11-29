#pragma once

#include "Component.hpp"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <Box2D/Common/b2Math.h>

class GameObject;

class WorldComponent : public Component {
public:
    explicit WorldComponent(GameObject *gameObject);

	// init components methods
    // void init(std::shared_ptr<sre::SpriteAtlas> spriteAtlas, int x, int y, int startSpriteId, int width, bool kinematic);
	void initTerrain(std::shared_ptr<sre::SpriteAtlas> spriteAtlas, std::vector<b2Vec2> positions, int size, int startSpriteId, int height);
	void initIsland(std::shared_ptr<sre::SpriteAtlas> spriteAtlas, std::vector<b2Vec2> points, int size, b2Vec2 position, float density);

    void moveTo(glm::vec2 tilePos);
    void update(float deltaTime) override;

    glm::vec2 getPosition();
	float GetPercOfTerrain();
	std::vector<std::vector<b2Vec2>> getRings();
	void WorldComponent::addRing(std::vector<b2Vec2> ring);

private:
	std::vector<std::vector<b2Vec2>> listOfRings;
    std::vector<std::shared_ptr<GameObject>> tiles;
	float percOfTerrain = 0.6;   
    bool kinematic;
    glm::vec2 pos;
    int width;
    float physicsScale;
};