//
// Created by codewing on 07.11.18.
//

#include "SimpleRenderer.hpp"
#include "ObjectManager.hpp"
#include "Physics.hpp"

SimpleRenderer::SimpleRenderer(SDL_Window* window) :
    r{window} {
}

void SimpleRenderer::render() {
    auto cameraObj = camera.lock();

    auto rp = sre::RenderPass::create()
            .withCamera(*cameraObj)
            .build();

    auto spriteBatchBuilder = sre::SpriteBatch::create();
    for (auto & renderComp : ObjectManager::instance.getRenderableComponents()){
        renderComp.renderSprite(spriteBatchBuilder);
    }

    auto sb = spriteBatchBuilder.build();
    rp.draw(sb);
}
