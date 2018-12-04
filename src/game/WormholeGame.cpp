//
// Created by codewing on 07.11.18.
//

#include "WormholeGame.hpp"
#include <glm/glm.hpp>
#include "../engine/debug/Log.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include "../engine/component/PhysicsComponent.hpp"
#include "MovementComponent.hpp"
#include "LevelGenerator.hpp"
#include <string>

class PhysicsObject;


void WormholeGame::update(float deltaTime) {

}

void WormholeGame::initialize() {

    auto sprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas("red_anim_Rabbit_Idle_000.png", "bunny");

    std::shared_ptr<GameObject> isi = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe");
    isi->setPosition({100, 600});
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(isi.get());
    spriteComp->setSprite(sprite);

    auto physicsComp = ObjectManager::GetInstance()->CreateComponent<PhysicsComponent>(isi.get());
    physicsComp->initCircle(b2_dynamicBody, sprite.getSpriteSize().x/2, isi->getPosition(), 0.0f);

    auto movementComp = ObjectManager::GetInstance()->CreateComponent<MovementComponent>(isi.get());

    LevelGenerator level({800,600}, 0.6);
    level.generateLevel();

    sre::Camera cam;
    cam.setOrthographicProjection(600,-1,1);
    auto x = 300;
    auto y = 500;
    glm::vec3 eye (x, y, 0);
    glm::vec3 at (x, y, -1);
    glm::vec3 up (0, 1, 0);
    cam.lookAt(eye, at, up);
    ObjectManager::GetInstance()->GetCameraManager().RegisterCamera("main", cam);
    ObjectManager::GetInstance()->GetCameraManager().SetActiveCamera("main");
}

WormholeGame::WormholeGame(EngineCore &engine) : GameModule(engine) {}
