//
// Created by codewing on 28.11.18.
//

#pragma once

#include <sre/SpriteBatch.hpp>
#include <sre/RenderPass.hpp>

class IRenderable {

public:
    virtual void onRenderSprite(sre::SpriteBatch::SpriteBatchBuilder &spriteBatchBuilder);
    virtual void onRender(sre::RenderPass& renderPass);
};
