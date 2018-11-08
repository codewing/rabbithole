//
// Created by codewing on 07.11.18.
//

#ifndef SIMPLERENDERENGINEPROJECT_RENDERER_H
#define SIMPLERENDERENGINEPROJECT_RENDERER_H

#include <sre/Renderer.hpp>
#include <SDL.h>
#include <glm/glm.hpp>

class SimpleRenderer {

private:
    sre::Renderer r;

public:
    SimpleRenderer(SDL_Window* window);

    void render();
};


#endif //SIMPLERENDERENGINEPROJECT_RENDERER_H
