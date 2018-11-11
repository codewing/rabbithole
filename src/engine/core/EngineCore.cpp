//
// Created by codewing on 07.11.18.
//

#include "EngineCore.hpp"
#include <SDL.h>

EngineCore::EngineCore(glm::ivec2 windowSize) {
    initSDLWindow(windowSize);

    renderer = std::make_unique<SimpleRenderer>(window);
    timer = std::make_unique<Timer>();
    input = std::make_unique<InputManager>();
    physics = std::make_unique<Physics>();
}

EngineCore::~EngineCore() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void EngineCore::initSDLWindow(glm::ivec2 windowSize) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    window = SDL_CreateWindow("Wormhole", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL);
}

void EngineCore::runGame() {
    isRunning = true;

    timer->start();

    while (isRunning){

        isRunning = input->handleInput();

        frameUpdate(timer->getDeltaTime());

        renderer->render();

        timer->tick();
    }
}
