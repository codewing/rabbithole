#include "GameObject.hpp"
#include <cassert>
#include <algorithm>
#include "Component.hpp"

GameObject::~GameObject(){
    // remove reference to this in components
    for (auto& c : components){
        c.lock()->gameObject = nullptr;
    }
}

void GameObject::removeUnusedComponents() {
    components.erase(
            std::remove_if(
                    components.begin(),
                    components.end(),
                    [](std::weak_ptr<Component> comp) {return comp.expired();}),
            components.end());

}

const glm::vec2 &GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(const glm::vec2 &position) {
    GameObject::position = position;
}

float GameObject::getRotation() const {
    return rotation;
}

void GameObject::setRotation(float rotation) {
    GameObject::rotation = rotation;
}

void GameObject::update(float deltaTime) {
    for (auto& comp : components){
        comp.lock()->update(deltaTime);
    }
}

const std::vector<std::weak_ptr<Component>> &GameObject::getComponents() {
    return components;
}

GameObject::GameObject(std::string name) {
    this->name = name;
}