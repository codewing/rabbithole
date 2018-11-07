//
// Created by codewing on 07.11.18.
//

#include "WormholeGame.hpp"
#include <SDL.h>

WormholeGame::WormholeGame(glm::ivec2 windowSize) {
    initSDLWindow(windowSize);

    renderer = std::make_unique<Renderer>(window);
}

WormholeGame::~WormholeGame() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void WormholeGame::initSDLWindow(glm::ivec2 windowSize) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    window = SDL_CreateWindow("Wormhole", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL);
}

void WormholeGame::runGame() {
    int i = 0;
    while(i < 100) {
        SDL_Delay(100);
        renderer->render();
        i++;
    }
}
