#include "SpriteAnimationComponent.hpp"
#include "../core/GameObject.hpp"
#include <memory>

SpriteAnimationComponent::SpriteAnimationComponent(GameObject *gameObject)
    : Component(gameObject, ComponentFlag::UPDATE) {}


void SpriteAnimationComponent::setSprites(std::vector<sre::Sprite> sprites) {
    this->sprites = sprites;

    auto spriteComponent = gameObject->getComponent<SpriteComponent>();
    spriteComponent->setSprite(sprites[spriteIndex]);
}

float SpriteAnimationComponent::getAnimationTime() const {
    return animationTime;
}

void SpriteAnimationComponent::setAnimationTime(float animationTime) {
    SpriteAnimationComponent::animationTime = animationTime;
}

void SpriteAnimationComponent::onUpdate(float deltaTime) {
    auto spriteComponent = gameObject->getComponent<SpriteComponent>();

    assert(spriteComponent != nullptr);

    time += deltaTime;

    if (time > animationTime){
        time = static_cast<float>(fmod(time, animationTime));
        spriteIndex++;

        if(destroyWhenDone && spriteIndex == sprites.size()) {
            // TODO DESTORY GAMEOBJECT
        } else {
            spriteIndex = static_cast<int>((spriteIndex) % sprites.size());
            spriteComponent->setSprite(sprites[spriteIndex]);
        }

    }
}

void SpriteAnimationComponent::setDestroyWhenDone(bool destroyWhenDone) {
    SpriteAnimationComponent::destroyWhenDone = destroyWhenDone;
}
