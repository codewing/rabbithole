//
// Created by codewing on 11.12.18.
//

#include "Projectile.hpp"
#include "../engine/core/ObjectManager.hpp"
#include "../engine/component/SpriteComponent.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "../engine/core/TextureSystem.hpp"


const Projectile Projectile::SHELL = Projectile("Shell", 8, 64, 100, 20, "bullet.png");

Projectile::Projectile(const std::string &name, float collisionRadius, float explosionRadius, float damage, float velocity,
                       const std::string &spriteName) : name(name), collisionRadius(collisionRadius), explosionRadius(explosionRadius), damage(damage),
                                                        velocity(velocity), spriteName(spriteName) {}

void Projectile::spawnProjectile(Projectile projectile, glm::vec2 direction, glm::vec2 position) {
    auto objManager = ObjectManager::GetInstance();

    auto projectileGO = objManager->CreateGameObject("Projectile " + glm::to_string(direction));

    auto projectileSprite = objManager->GetTextureSystem().getSpriteFromAtlas(projectile.getSpriteName(), "projectiles");
    auto spriteComponent = objManager->CreateComponent<SpriteComponent>(projectileGO.get());
    spriteComponent->setSprite(projectileSprite);

    auto physicsComponent = objManager->CreateComponent<PhysicsComponent>(projectileGO.get());
    physicsComponent->initCircle(b2_dynamicBody, projectile.getCollisionRadius(), position, 1.0f);
}

const std::string &Projectile::getName() const {
    return name;
}

float Projectile::getExplosionRadius() const {
    return explosionRadius;
}

float Projectile::getDamage() const {
    return damage;
}

float Projectile::getVelocity() const {
    return velocity;
}

const std::string &Projectile::getSpriteName() const {
    return spriteName;
}

float Projectile::getCollisionRadius() const {
    return collisionRadius;
}
