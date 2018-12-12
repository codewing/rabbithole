//
// Created by codewing on 11.12.18.
//

#include "Projectile.hpp"

Projectile::Projectile(float explosionRadius, float damage, float velocity) : explosionRadius(explosionRadius),
                                                                              damage(damage), velocity(velocity) {}

void Projectile::spawnProjectile(Projectile projectile, glm::vec2 direction, glm::vec2 position) {

}
