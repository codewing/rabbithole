//
// Created by codewing on 07.11.18.
//

#pragma once

#include <sre/Renderer.hpp>
#include <glm/glm.hpp>
#include <memory>

#ifdef DEBUG_PHYSICS
#include "../debug/Box2DDebugDraw.hpp"
#endif
#include "PhysicsSystem.hpp"

class SDL_Window;

class SimpleRenderer {

private:
    sre::Renderer r;

#ifdef DEBUG_PHYSICS
    Box2DDebugDraw debugDraw;
#endif

public:
    SimpleRenderer(SDL_Window* window);

    void renderFrame();
};
