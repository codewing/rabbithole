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
#include "Level.hpp"
#include <string>

class PhysicsObject;


void WormholeGame::update(float deltaTime) {

}

void WormholeGame::initialize() {

    auto sprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas("bird1.png", "bird");

    std::shared_ptr<GameObject> isi = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe");
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(isi.get());
    spriteComp->setSprite(sprite);

    auto movementComp = ObjectManager::GetInstance()->CreateComponent<MovementComponent>(isi.get());

    auto physicsComp = ObjectManager::GetInstance()->CreateComponent<PhysicsComponent>(isi.get());
    physicsComp->initCircle(b2_staticBody, sprite.getSpriteSize().x, glm::vec2{0,0}, 0.0f);

    Level level({800,600}, 0.6);
    level.generateLevel();

    sre::Camera cam;
    cam.setOrthographicProjection(600,-1,1);
    glm::vec3 eye (300, 300, 0);
    glm::vec3 at (300, 300, -1);
    glm::vec3 up (0, 1, 0);
    cam.lookAt(eye, at, up);
    ObjectManager::GetInstance()->GetCameraManager().RegisterCamera("main", cam);
    ObjectManager::GetInstance()->GetCameraManager().SetActiveCamera("main");
}

WormholeGame::WormholeGame(EngineCore &engine) : GameModule(engine) {}
