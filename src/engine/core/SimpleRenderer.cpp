//
// Created by codewing on 07.11.18.
//

#include <SDL.h>

#include "SimpleRenderer.hpp"
#include "ObjectManager.hpp"
#include "PhysicsSystem.hpp"

#ifdef DEBUG_PHYSICS
SimpleRenderer::SimpleRenderer(SDL_Window* window) :
        r{window, false}, debugDraw{PhysicsSystem::PHYSICS_SCALE} {
    ObjectManager::GetInstance()->GetPhysicsWorld()->SetDebugDraw(&debugDraw);
}
#else
SimpleRenderer::SimpleRenderer(SDL_Window* window) :
    r{window, false} {
}
#endif

void SimpleRenderer::renderFrame() {
    auto cameraObj = ObjectManager::GetInstance()->GetCameraManager().GetActiveCamera();

    auto rp = sre::RenderPass::create()
            .withCamera(*cameraObj)
            .build();

    auto spriteBatchBuilder = sre::SpriteBatch::create();
    for (auto& renderComp : ObjectManager::GetInstance()->GetRenderableComponents()){
        renderComp->onRenderSprite(spriteBatchBuilder);
    }

    auto sb = spriteBatchBuilder.build();

#ifdef DEBUG_PHYSICS
    ObjectManager::GetInstance()->GetPhysicsWorld()->DrawDebugData();
    rp.drawLines(debugDraw.getLines());
    debugDraw.clear();
#endif

    rp.draw(sb);
    rp.finish();
    r.swapWindow();
}
