//
// Created by codewing on 21.11.18.
//

#include "GraphicsSystem.hpp"

GraphicsSystem::GraphicsSystem(SDL_Window *window) {
    renderer = std::make_unique<SimpleRenderer>(window);
    textureSystem = std::make_unique<TextureSystem>();
}

void GraphicsSystem::render() {
    renderer->renderFrame();
}

TextureSystem &GraphicsSystem::getTextureSystem() {
    return *(textureSystem.get());
}

SimpleRenderer &GraphicsSystem::getRenderer() {
    return *(renderer.get());
}
