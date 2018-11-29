//
// Created by codewing on 07.11.18.
//

#pragma once

#include "GraphicsSystem.hpp"
#include "Timer.hpp"
#include "InputManager.hpp"
#include "PhysicsSystem.hpp"
#include "ObjectManager.hpp"
#include "TextureSystem.hpp"
#include "GameModule.hpp"


#include <glm/glm.hpp>
#include <memory>

class EngineCore {

public:
    EngineCore(std::string windowName, glm::ivec2 windowSize);
    ~EngineCore();

    GraphicsSystem& getGraphicsSystem();
    PhysicsSystem& getPhysicsSystem();

private:
    bool isRunning = false;

    SDL_Window *window = nullptr;

    std::unique_ptr<GraphicsSystem> graphics;
    std::unique_ptr<Timer> timer;
    std::unique_ptr<InputManager> input;
    std::unique_ptr<PhysicsSystem> physics;

    void runGame(GameModule& gameModule);
    void update(float deltaTime);

    void initSDLWindow(std::string windowName, glm::ivec2 windowSize);

    friend int main(int argc, char** argv);
};
