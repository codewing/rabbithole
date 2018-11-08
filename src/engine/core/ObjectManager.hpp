//
// Created by codewing on 08.11.18.
//

#ifndef SIMPLERENDERENGINEPROJECT_OBJECTMANAGER_HPP
#define SIMPLERENDERENGINEPROJECT_OBJECTMANAGER_HPP


#include <vector>
#include "GameObject.hpp"
#include "../component/SpriteComponent.hpp"

class ObjectManager {

public:
    static ObjectManager instance;

    void init();

    void registerRenderable();
    void deRegisterRenderable();

    void registerPhysicsComponent();
    void deRegisterPhysicsComponent();

private:
    std::vector<GameObject> gameobjectList;

    std::vector<SpriteComponent> spriteComponentList;
    std::vector<PhysicsComponent> physicsComponentList;

};


#endif //SIMPLERENDERENGINEPROJECT_OBJECTMANAGER_HPP
