//
// Created by codewing on 07.11.18.
//

#include "WormholeGame.hpp"
#include <glm/glm.hpp>
#include "../engine/debug/Log.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include "MovementComponent.hpp"
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

    sre::Camera cam;
    cam.setOrthographicProjection(600,-1,1);
    glm::vec3 eye (300, 300, 0);
    glm::vec3 at (300, 300, -1);
    glm::vec3 up (0, 1, 0);
    cam.lookAt(eye, at, up);
    ObjectManager::GetInstance()->getCameraManager().RegisterCamera("main", cam);
    ObjectManager::GetInstance()->getCameraManager().SetActiveCamera("main");
}

WormholeGame::WormholeGame(EngineCore &engine) : GameModule(engine) {}
