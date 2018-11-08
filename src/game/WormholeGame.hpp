//
// Created by codewing on 07.11.18.
//

#ifndef SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H
#define SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H

#include "../engine/core/EngineCore.hpp"
#include <memory>

class WormholeGame {
public:
    WormholeGame();

private:
    std::unique_ptr<EngineCore> engine;

    void update(float deltaTime);
};


#endif //SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H
