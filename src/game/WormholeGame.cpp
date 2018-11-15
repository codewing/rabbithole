//
// Created by codewing on 07.11.18.
//

#include "WormholeGame.hpp"
#include <glm/glm.hpp>
#include "../engine/debug/Log.hpp"
#include "../engine/core/ObjectManager.hpp"
#include <string>

class PhysicsObject;

WormholeGame::WormholeGame() {
    engine = std::make_unique<EngineCore>("Wormhole Game", glm::ivec2(800,600));
    engine->frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };

    GameObject* isi = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe");
    ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(isi);

    sre::Camera cam;
    ObjectManager::GetInstance()->getCameraManager().RegisterCamera("main", &cam);
    ObjectManager::GetInstance()->getCameraManager().SetActiveCamera("main");

    LOG_GAME_INFO("Engine booted!");
    engine->runGame();
}

void WormholeGame::update(float deltaTime) {

}
