//
// Created by codewing on 07.11.18.
//

#include "WormholeGame.hpp"
#include <glm/glm.hpp>
#include "../engine/debug/Log.hpp"

WormholeGame::WormholeGame() {
    engine = std::make_unique<EngineCore>(glm::ivec2(800,600));
    engine->frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };
    LOG_GAME_INFO("Engine booted!");
    engine->runGame();
}

void WormholeGame::update(float deltaTime) {

}
