#pragma once

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "sre/SpriteBatch.hpp"

// Forward declaration
class Component;

// GameObject are empty container objects, which contains Components
class GameObject {
public:

    ~GameObject();

    template <class T>
    T* addComponent(T* component);

    template <class T>                                   //  Get component of a given type to a gameObject. If not found return empty shared_ptr (==nullptr). example:
    T* getComponent();                   // std::shared_ptr<SpriteComponent> spriteComponent = gameObject->getComponent<SpriteComponent>();

    void update(float deltaTime);

    const glm::vec2 &getPosition() const;

    void setPosition(const glm::vec2 &position);

    float getRotation() const;

    void setRotation(float rotation);

    const std::vector<Component*>& getComponents();

    std::string name = "_";
private:
    explicit GameObject(std::string name);
    std::vector<Component*> components;

    glm::vec2 position;
    float rotation;

    friend class ObjectManager;
};

// definition of the template member function addComponent(Component* comp)
// Usage:
// GameObject* go = something;
//
// SpriteComponent* sc = go->addComponent<SpriteComponent>();
template <class T>
inline T* GameObject::addComponent(T* component){
    components.push_back(component);

    return component;
}

// definition of the template member function addComponent
// Usage:
// GameObject* go = something;
// SpriteComponent* sc = go->getComponent<SpriteComponent>();
template <class T>
inline T* GameObject::getComponent(){
    for (auto& c : components){
        T* res = dynamic_cast<T*>(c);
        if (res != nullptr){
            return res;
        }
    }
    return nullptr;
}
