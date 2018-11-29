//
// Created by codewing on 29.11.18.
//

#include "RingInteractable.hpp"

void RingInteractable::onCollisionStart(IInteractable *interactable) {

}

void RingInteractable::onCollisionEnd(IInteractable *interactable) {

}

void RingInteractable::setPosition(glm::vec2 newPosition) {}

void RingInteractable::setRotation(float newAngle) {}

RingInteractable::RingInteractable(WorldComponent* worldComponent, std::vector<b2Vec2> ringData)
    : worldComponent(worldComponent), ringData(ringData) {
    initChain(b2BodyType::b2_staticBody, ringData, {0, 0}, 1);
}
