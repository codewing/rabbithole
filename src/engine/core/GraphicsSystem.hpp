//
// Created by codewing on 21.11.18.
//


#pragma once

#include <memory>

#include "SimpleRenderer.hpp"
#include "TextureSystem.hpp"

class SDL_Window;

class GraphicsSystem {

public:
    GraphicsSystem(SDL_Window* window);

    const TextureSystem& getTextureSystem();
    const SimpleRenderer& getRenderer();

private:
    void render();

    std::unique_ptr<SimpleRenderer> renderer;
    std::unique_ptr<TextureSystem> textureSystem;

    friend class EngineCore;
};


