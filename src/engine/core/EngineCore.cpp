//
// Created by codewing on 07.11.18.
//

#include "EngineCore.hpp"
#include "../debug/Log.hpp"
#include <SDL.h>

#define SDL_MAIN_HANDLED

EngineCore::EngineCore(std::string windowName, glm::ivec2 windowSize) {
    Log::initialize();

    initSDLWindow(windowName, windowSize);

    graphics = std::make_unique<GraphicsSystem>(window);
    timer = std::make_unique<Timer>();
    input = std::make_unique<InputManager>();
    physics = std::make_unique<Physics>();

    LOG_ENGINE_INFO("All systems successfully initialized!");
}

EngineCore::~EngineCore() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void EngineCore::initSDLWindow(std::string windowName, glm::ivec2 windowSize) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
}

void EngineCore::runGame(GameModule& gameModule) {
    isRunning = true;

    gameModule.initialize();

    timer->start();

    while (isRunning){

        isRunning = input->handleInput();

        gameModule.update(timer->getDeltaTime());
        update(timer->getDeltaTime());

        physics->update(timer->getDeltaTime());

        graphics->render();

        timer->tick();
    }
}

const GraphicsSystem& EngineCore::getGraphicsSystem() {
    return *(graphics.get());
}

void EngineCore::update(float deltaTime) {
    //TODO update all components
}
