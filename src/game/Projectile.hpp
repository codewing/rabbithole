//
// Created by codewing on 11.12.18.
//

#pragma once

#include <string>
#include <glm/vec2.hpp>

class Projectile {

public:
    static const Projectile SHELL;

    static void spawnProjectile(Projectile projectile, glm::vec2 direction, glm::vec2 position);

private:
public:
    Projectile(const std::string &name, float collisionRadius, float explosionRadius, float damage, float velocity,
               float fireCooldown, const std::string &spriteName);

    const std::string &getName() const;
    float getExplosionRadius() const;
    float getDamage() const;
    float getVelocity() const;
    float getCollisionRadius() const;
    const std::string &getSpriteName() const;

    float getFireCooldown() const;

private:

    std::string name;
    float collisionRadius;
    float explosionRadius;
    float damage;
    float velocity;
    float fireCooldown;
    std::string spriteName;

};



