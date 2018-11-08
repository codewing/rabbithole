//
// Created by codewing on 07.11.18.
//

#ifndef SIMPLERENDERENGINEPROJECT_ENGINECORE_H
#define SIMPLERENDERENGINEPROJECT_ENGINECORE_H

#include "SimpleRenderer.hpp"
#include "Timer.hpp"
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
    bool isRunning;

    SDL_Window *window;
    std::unique_ptr<SimpleRenderer> renderer;
    std::unique_ptr<Timer> timer;

    void initialize();
    void initSDLWindow(glm::ivec2 windowSize);

};


#endif //SIMPLERENDERENGINEPROJECT_ENGINECORE_H
