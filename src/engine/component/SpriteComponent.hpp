#pragma once

#include "../core/Component.hpp"
#include "sre/Sprite.hpp"
#include "../core/IRenderable.hpp"

class SpriteComponent : public Component, public IRenderable {
public:
    explicit SpriteComponent(GameObject *gameObject);

    virtual void renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);

    virtual void onRender();

    void setSprite(const sre::Sprite& sprite);
    sre::Sprite getSprite();
private:
    sre::Sprite sprite;
};

