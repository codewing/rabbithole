//
// Created by codewing on 04.12.18.
//

#include "Rabbit.hpp"

#include "../engine/core/GameObject.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include "MovementComponent.hpp"

Rabbit::Rabbit(EngineCore& engine, const std::string& team, glm::vec2 position) : engine(engine), team{team} {
    spawnRabbitBase(position);
    spawnRabbitWeapon(position);
}

void Rabbit::spawnRabbitBase(glm::vec2 position) {
    auto baseSprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas(team + "_anim_Rabbit_Idle_000.png", "bunny");

    rabbitBase = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe ("+team+")");
    rabbitBase->setPosition(position);
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(rabbitBase.get());
    spriteComp->setSprite(baseSprite);

    auto physicsComp = ObjectManager::GetInstance()->CreateComponent<PhysicsComponent>(rabbitBase.get());
    physicsComp->initCircle(b2_dynamicBody, baseSprite.getSpriteSize().x/2, rabbitBase->getPosition(), 0.0f);

    auto movementComp = ObjectManager::GetInstance()->CreateComponent<MovementComponent>(rabbitBase.get());
}

void Rabbit::spawnRabbitWeapon(glm::vec2 position) {
    auto weaponSprite = engine.getGraphicsSystem().getTextureSystem().getSpriteFromAtlas("bunny_hand_right_with_bazooka.png", "bunny");

    rabbitWeapon = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe ("+team+") Weapon");
    rabbitWeapon->setPosition(rabbitBase->getPosition());
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(rabbitWeapon.get());
    weaponSprite.setOrderInBatch(10);
    spriteComp->setSprite(weaponSprite);

}
