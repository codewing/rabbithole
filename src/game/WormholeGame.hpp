//
// Created by codewing on 07.11.18.
//

#ifndef SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H
#define SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H

#include "../engine/core/EngineCore.hpp"
#include "../engine/core/GameModule.hpp"
#include <memory>

class WormholeGame : public GameModule {
public:
    WormholeGame(EngineCore &engine);

private:

    void initialize() override;
    void update(float deltaTime);
};


#endif //SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H
