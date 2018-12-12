//
// Created by codewing on 12.12.18.
//

#include "ProjectilePhysicsComponent.hpp"

#include "../engine/core/ObjectManager.hpp"
#include "../engine/component/SpriteComponent.hpp"
#include "../engine/component/SpriteAnimationComponent.hpp"
#include "../engine/core/TextureSystem.hpp"


ProjectilePhysicsComponent::ProjectilePhysicsComponent(GameObject *gameObject) : PhysicsComponent(gameObject) {}

void ProjectilePhysicsComponent::onCollisionStart(IInteractable *interactable) {
    if(!interactable->isSensor()) {
        auto objManager = ObjectManager::GetInstance();

        auto explosionGO = objManager->CreateGameObject("Explosion");
        explosionGO->setLocalPosition(gameObject->getPosition());
        explosionGO->setLocalRotation(gameObject->getRotation());

        auto spriteComponent = objManager->CreateComponent<SpriteComponent>(explosionGO.get());

        std::vector<sre::Sprite> explosionSprites = objManager->GetTextureSystem().getSpritesFromAtlas(explosionSpriteNames, "projectiles");
        auto spriteAnimComponent = objManager->CreateComponent<SpriteAnimationComponent>(explosionGO.get());
        spriteAnimComponent->setSprites(explosionSprites);
        spriteAnimComponent->setAnimationTime(0.016f);
        spriteAnimComponent->setDestroyWhenDone(true);

        // TODO destroy self
    }
}
