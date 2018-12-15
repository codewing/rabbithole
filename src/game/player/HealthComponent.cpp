//
// Created by codewing on 15.12.18.
//

#include "HealthComponent.hpp"

HealthComponent::HealthComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::NONE) {}

float HealthComponent::getHealthValue() const {
    return healthValue;
}

void HealthComponent::setHealthValue(float healthValue) {
    HealthComponent::healthValue = healthValue;
}

void HealthComponent::applyDamage(float amount) {
    HealthComponent::healthValue -= amount;
}
