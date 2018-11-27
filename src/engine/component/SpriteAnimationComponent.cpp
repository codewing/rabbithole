//
// Created by Morten Nobel-Jørgensen on 10/10/2017.
//

#include "SpriteAnimationComponent.hpp"
#include "../core/GameObject.hpp"
#include <memory>

SpriteAnimationComponent::SpriteAnimationComponent(GameObject *gameObject)
    : Component(gameObject, ComponentFlag::RENDERABLE & ComponentFlag::UPDATE) {}

void SpriteAnimationComponent::update(float deltaTime) {
    auto spriteComponent = gameObject->getComponent<SpriteComponent>();

    assert(spriteComponent != nullptr);

    time += deltaTime;

    if (time > animationTime){
        time = static_cast<float>(fmod(time, animationTime));
        spriteIndex = static_cast<int>((spriteIndex + 1) % sprites.size());
        spriteComponent->setSprite(sprites[spriteIndex]);
    }
}

void SpriteAnimationComponent::setSprites(std::vector<sre::Sprite> sprites) {
    this->sprites = sprites;
}

float SpriteAnimationComponent::getAnimationTime() const {
    return animationTime;
}

void SpriteAnimationComponent::setAnimationTime(float animationTime) {
    SpriteAnimationComponent::animationTime = animationTime;
}
