//
// Created by codewing on 07.11.18.
//

#include "EngineCore.hpp"
#include "../debug/Log.hpp"
#include <SDL.h>
#include "ObjectManager.hpp"

#define SDL_MAIN_HANDLED

EngineCore::EngineCore(std::string windowName, glm::ivec2 windowSize) {
    Log::initialize();

    initSDLWindow(windowName, windowSize);

    timer = std::make_unique<Timer>();
    input = std::make_unique<InputManager>();
    physics = std::make_unique<PhysicsSystem>();
    ObjectManager::GetInstance()->setEngineCore(this);
    graphics = std::make_unique<GraphicsSystem>(window);

    LOG_ENGINE_INFO("All systems successfully initialized!");
}

EngineCore::~EngineCore() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void EngineCore::initSDLWindow(std::string windowName, glm::ivec2 windowSize) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
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
        timer->tick();

        isRunning = input->handleInput();

        gameModule.update(timer->getDeltaTime());
        update(timer->getDeltaTime());

        physics->update(timer->getDeltaTime());

        graphics->render();
    }
}

GraphicsSystem& EngineCore::getGraphicsSystem() {
    return *(graphics.get());
}

void EngineCore::update(float deltaTime) {
    for(auto& updatableComponent : ObjectManager::GetInstance()->GetUpdatableComponents()) {
        updatableComponent->onUpdate(deltaTime);
    }
}

PhysicsSystem &EngineCore::getPhysicsSystem() {
    return *(physics.get());
}
