//
// Created by codewing on 07.11.18.
//

#pragma once

#include "GraphicsSystem.hpp"
#include "Timer.hpp"
#include "InputManager.hpp"
#include "Physics.hpp"
#include "ObjectManager.hpp"
#include "TextureSystem.hpp"
#include "GameModule.hpp"


#include <glm/glm.hpp>
#include <memory>

class EngineCore {

public:
    EngineCore(std::string windowName, glm::ivec2 windowSize);
    ~EngineCore();

    void runGame(GameModule& gameModule);

    const GraphicsSystem& getGraphicsSystem();

private:
    bool isRunning = false;

    SDL_Window *window = nullptr;

    std::unique_ptr<GraphicsSystem> graphics;
    std::unique_ptr<Timer> timer;
    std::unique_ptr<InputManager> input;
    std::unique_ptr<Physics> physics;

    void initSDLWindow(std::string windowName, glm::ivec2 windowSize);
    void update(float deltaTime);

};
