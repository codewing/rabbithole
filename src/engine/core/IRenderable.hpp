//
// Created by codewing on 28.11.18.
//

#pragma once

#include <sre/SpriteBatch.hpp>

class IRenderable {

public:
    virtual void onRenderSprite(sre::SpriteBatch::SpriteBatchBuilder &spriteBatchBuilder);

};
