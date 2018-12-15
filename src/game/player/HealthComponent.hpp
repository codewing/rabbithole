//
// Created by codewing on 15.12.18.
//

#pragma once


#include "../../engine/core/Component.hpp"

class HealthComponent : public Component {
public:
    HealthComponent(GameObject *gameObject);

    float getHealthValue() const;

    void setHealthValue(float healthValue);

    void applyDamage(float amount);

private:
    float healthValue = 0;
};

