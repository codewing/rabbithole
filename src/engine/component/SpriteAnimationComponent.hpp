#pragma once

#include "../core/Component.hpp"
#include "sre/Sprite.hpp"
#include "SpriteComponent.hpp"
#include "../core/IUpdatable.hpp"

class SpriteAnimationComponent: public Component, public IUpdatable {
public:
    SpriteAnimationComponent(GameObject *gameObject);

    void setSprites(std::vector<sre::Sprite> sprites);      // sprite sequence

    void onUpdate(float deltaTime) override;

    float getAnimationTime() const;                         // time between animations (in seconds)
    void setAnimationTime(float animationTime);

    void setDestroyWhenDone(bool destroyWhenDone);

private:
    float animationTime = 0.300f;
    std::vector<sre::Sprite> sprites;
    float time = 0;
    int spriteIndex = 0;

    bool destroyWhenDone = false;
};


