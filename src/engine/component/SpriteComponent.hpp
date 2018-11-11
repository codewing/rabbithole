#pragma once

#include "../core/Component.hpp"
#include "sre/Sprite.hpp"

class SpriteComponent : public Component {
public:
    explicit SpriteComponent(GameObject *gameObject);

    virtual void renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);

    void setSprite(const sre::Sprite& sprite);
    sre::Sprite getSprite();
private:
    sre::Sprite sprite;
};

