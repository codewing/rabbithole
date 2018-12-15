//
// Created by codewing on 04.12.18.
//

#include "Rabbit.hpp"

#include "../../engine/core/GameObject.hpp"
#include "../../engine/core/ObjectManager.hpp"
#include "../../engine/component/SpriteComponent.hpp"
#include "MovementComponent.hpp"
#include "RabbitPhysicsComponent.hpp"
#include "WeaponControllerComponent.hpp"
#include "HealthComponent.hpp"

Rabbit::Rabbit(const std::string& team, glm::vec2 position, int gamepadID) : team{team} {
    spawnRabbitBase(position, gamepadID);
    spawnRabbitWeapon(gamepadID);
}

void Rabbit::spawnRabbitBase(glm::vec2 position, int gamepadID) {
    auto movementSpriteNames = {team + "_anim_Rabbit_Movement_000.png", team + "_anim_Rabbit_Movement_001.png"};
    auto idleSpriteNames =     {team + "_anim_Rabbit_Idle_000.png", team + "_anim_Rabbit_Idle_001.png",
                                team + "_anim_Rabbit_Idle_002.png", team + "_anim_Rabbit_Idle_003.png"};

    std::vector<sre::Sprite> movementSprites = ObjectManager::GetInstance()->GetTextureSystem().getSpritesFromAtlas(movementSpriteNames, "bunny");
    std::vector<sre::Sprite> idleSprites = ObjectManager::GetInstance()->GetTextureSystem().getSpritesFromAtlas(idleSpriteNames, "bunny");
    auto setSpritePosition = [](sre::Sprite& sprite) { sprite.setOrderInBatch(10); };
    std::for_each(movementSprites.begin(), movementSprites.end(), setSpritePosition);
    std::for_each(idleSprites.begin(), idleSprites.end(), setSpritePosition);

    rabbitBase = ObjectManager::GetInstance()->CreateGameObject("Rabbit_"+team);
    rabbitBase->setLocalPosition(position);
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(rabbitBase.get());

    basePhysicsComponent = ObjectManager::GetInstance()->CreateComponent<RabbitPhysicsComponent>(rabbitBase.get());
    basePhysicsComponent->initCircle(b2_dynamicBody, 25, rabbitBase->getLocalPosition(), 0.0f);

    auto movementComp = ObjectManager::GetInstance()->CreateComponent<MovementComponent>(rabbitBase.get());
    movementComp->setupControllerInput(gamepadID);
    movementComp->setupSprites(spriteComp.get(), idleSprites, movementSprites);

    healthComponent = ObjectManager::GetInstance()->CreateComponent<HealthComponent>(rabbitBase.get());
    healthComponent->setHealthValue(100);
}

void Rabbit::spawnRabbitWeapon(int gamepadID) {
    auto weaponSprite = ObjectManager::GetInstance()->GetTextureSystem().getSpriteFromAtlas("bunny_hand_right_with_bazooka.png", "bunny");

    rabbitWeapon = ObjectManager::GetInstance()->CreateGameObject("IsiLiebe ("+team+") Weapon");
    rabbitWeapon->setParent(rabbitBase.get());
    rabbitWeapon->setLocalPosition({0, 10});
    auto spriteComp = ObjectManager::GetInstance()->CreateComponent<SpriteComponent>(rabbitWeapon.get());
    spriteComp->setSprite(weaponSprite);

    auto weaponControllerComp = ObjectManager::GetInstance()->CreateComponent<WeaponControllerComponent>(rabbitWeapon.get());
    weaponSprite.setOrderInBatch(5);
    weaponControllerComp->setWeaponSprite(weaponSprite);
    weaponControllerComp->setReferenceToSpriteComponent(spriteComp.get());
    weaponControllerComp->setGamepadID(gamepadID);
    weaponControllerComp->setMovementComponent(rabbitBase->getComponent<MovementComponent>().get());
}

glm::vec2 Rabbit::getPosition() {
    return rabbitBase->getLocalPosition();
}

float Rabbit::getHealthValue() {
    return healthComponent->getHealthValue();
}

RabbitPhysicsComponent *Rabbit::getRabbitPhysicsComponent() {
    return basePhysicsComponent.get();
}
