//
// Created by codewing on 07.11.18.
//

#ifndef SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H
#define SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H

#include "../engine/Renderer.h"
#include <glm/glm.hpp>
#include <memory>

class SDL_Window;

class WormholeGame {

public:
    WormholeGame(glm::ivec2 windowSize);
    ~WormholeGame();

    void runGame();

private:
    SDL_Window *window;
    std::unique_ptr<Renderer> renderer;

    void initSDLWindow(glm::ivec2 windowSize);

};


#endif //SIMPLERENDERENGINEPROJECT_WORMHOLEGAME_H
