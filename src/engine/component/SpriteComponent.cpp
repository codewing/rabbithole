//
// Created by Morten Nobel-Jørgensen on 10/10/2017.
//

#include "SpriteComponent.hpp"
#include "../core/GameObject.hpp"

SpriteComponent::SpriteComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::RENDERABLE) {}

void SpriteComponent::setSprite(const sre::Sprite &sprite) {
    this->sprite = sprite;
}

sre::Sprite SpriteComponent::getSprite() {
    return sprite;
}

void SpriteComponent::onRenderSprite(sre::SpriteBatch::SpriteBatchBuilder &spriteBatchBuilder) {
    sprite.setPosition(gameObject->getPosition());
    sprite.setRotation(gameObject->getRotation());
    spriteBatchBuilder.addSprite(sprite);
}
