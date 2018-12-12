//
// Created by codewing on 11.12.18.
//

#pragma once

#include <glm/vec2.hpp>


class Projectile {

public:
    static const Projectile BAZOOKA;

    static void spawnProjectile(Projectile projectile, glm::vec2 direction, glm::vec2 position);

private:
    Projectile(float explosionRadius, float damage, float velocity);

    float explosionRadius;
    float damage;
    float velocity;
};

const Projectile Projectile::BAZOOKA = Projectile(64, 100, 20);



