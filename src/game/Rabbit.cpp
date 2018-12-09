//
// Created by codewing on 04.12.18.
//

#include "Rabbit.hpp"

#include "../engine/core/GameObject.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include "MovementComponent.hpp"
#include "RabbitPhysicsComponent.hpp"

Rabbit::Rabbit(EngineCore& engine, const std::string& team, glm::vec2 position, int gamepadID) : engine(engine), team{team} {
    spawnRabbitBase(position, gamepadID);
    spawnRabbitWeapon(position);
}

void Rabbit::spawnRabbitBase(glm::vec2 position, int gamepadID) {
    auto baseSprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas(team + "_anim_Rabbit_Idle_000.png", "bunny");

    rabbitBase = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe ("+team+")");
    rabbitBase->setLocalPosition(position);
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(rabbitBase.get());
    baseSprite.setOrderInBatch(10);
    spriteComp->setSprite(baseSprite);

    auto physicsComp = ObjectManager::GetInstance()->CreateComponent<RabbitPhysicsComponent>(rabbitBase.get());
    physicsComp->initCircle(b2_dynamicBody, baseSprite.getSpriteSize().x/3, rabbitBase->getLocalPosition(), 0.0f);

    auto movementComp = ObjectManager::GetInstance()->CreateComponent<MovementComponent>(rabbitBase.get());
    movementComp->setupControllerInput(gamepadID);
}

void Rabbit::spawnRabbitWeapon(glm::vec2 position) {
    auto weaponSprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas("bunny_hand_right_with_bazooka.png", "bunny");

    rabbitWeapon = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe ("+team+") Weapon");
    rabbitWeapon->setParent(rabbitBase.get());
    rabbitWeapon->setLocalPosition({0, 10});
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(rabbitWeapon.get());
    weaponSprite.setOrderInBatch(5);
    spriteComp->setSprite(weaponSprite);

}

glm::vec2 Rabbit::getPosition() {
    return rabbitBase->getLocalPosition();
}
