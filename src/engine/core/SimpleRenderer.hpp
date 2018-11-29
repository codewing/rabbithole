//
// Created by codewing on 07.11.18.
//

#pragma once

#include <sre/Renderer.hpp>
#include <glm/glm.hpp>
#include <memory>

#include "../debug/Box2DDebugDraw.hpp"
#include "PhysicsSystem.hpp"

class SDL_Window;

class SimpleRenderer {

private:
    sre::Renderer r;

public:
    SimpleRenderer(SDL_Window* window);

    void renderFrame();
};
