//
// Created by codewing on 07.11.18.
//

#pragma once

#include "SimpleRenderer.hpp"
#include "Timer.hpp"
#include "InputManager.hpp"
#include "Physics.hpp"

#include <glm/glm.hpp>
#include <memory>

class SDL_Window;

class EngineCore {

public:
    EngineCore(glm::ivec2 windowSize);
    ~EngineCore();

    void runGame();

    std::function<void(float deltaTimeSec)> frameUpdate;

private:
    bool isRunning = false;

    SDL_Window *window = nullptr;
    std::unique_ptr<SimpleRenderer> renderer;
    std::unique_ptr<Timer> timer;
    std::unique_ptr<InputManager> input;
    std::unique_ptr<Physics> physics;

    void initSDLWindow(glm::ivec2 windowSize);

};
