#include "game/WormholeGame.hpp"
#undef main

int main(int argc, char** argv) {

    EngineCore engine {"Wormhole Game", glm::ivec2(800,600)};
    WormholeGame game {engine};

    engine.runGame(game);

    return 0;
};