//
// Created by codewing on 07.11.18.
//

#include "SimpleRenderer.hpp"
#include "ObjectManager.hpp"
#include "Physics.hpp"

SimpleRenderer::SimpleRenderer(SDL_Window* window) :
    r{window} {
}

void SimpleRenderer::renderFrame() {
    auto cameraObj = ObjectManager::GetInstance()->getCameraManager().GetActiveCamera();

    auto rp = sre::RenderPass::create()
            .withCamera(*cameraObj)
            .withClearColor(true, sre::Color{0.2f, 0.2f, 0.2f, 1.0f})
            .build();

    auto spriteBatchBuilder = sre::SpriteBatch::create();
    for (auto& renderComp : ObjectManager::GetInstance()->getRenderableComponents()){
        renderComp->renderSprite(spriteBatchBuilder);
    }

    auto sb = spriteBatchBuilder.build();
    rp.draw(sb);
}
