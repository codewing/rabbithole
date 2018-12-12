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

    explicit GameObject(std::string name);

    ~GameObject();

    template <class T>
    std::shared_ptr<T> addComponent(std::shared_ptr<T> component);

    template <class T>                                   //  Get component of a given type to a gameObject. If not found return empty shared_ptr (==nullptr). example:
    std::shared_ptr<T> getComponent();                   // std::shared_ptr<SpriteComponent> spriteComponent = gameObject->getComponent<SpriteComponent>();

    const glm::vec2 &getLocalPosition() const;
    const glm::vec2 getPosition() const;

    void setLocalPosition(const glm::vec2 &position);

    float getLocalRotation() const;
    float getRotation() const;
    void setLocalRotation(float rotation);

    GameObject* getParent() const;
    void setParent(GameObject* parent);

    const std::vector<std::shared_ptr<Component>>& getComponents();
    std::string name = "_";
private:
    std::vector<std::shared_ptr<Component>> components;

    glm::vec2 position = glm::vec2{0, 0};
    GameObject* parent = nullptr;

    float rotation;

    void removeComponent(Component* component);

    friend class ObjectManager;
};

// definition of the template member function addComponent(Component* comp)
// Usage:
// GameObject* go = something;
//
// SpriteComponent* sc = go->addComponent<SpriteComponent>();
template <class T>
inline std::shared_ptr<T> GameObject::addComponent(std::shared_ptr<T> component){
    components.push_back(component);

    return component;
}

// definition of the template member function addComponent
// Usage:
// GameObject* go = something;
// SpriteComponent* sc = go->getComponent<SpriteComponent>();
template <class T>
inline std::shared_ptr<T> GameObject::getComponent(){
    for (auto& c : components){
        std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(c);
        if (res != nullptr){
            return res;
        }
    }
    return nullptr;
}
