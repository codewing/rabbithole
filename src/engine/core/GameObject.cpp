#include "GameObject.hpp"
#include <cassert>
#include <algorithm>
#include "Component.hpp"

GameObject::~GameObject(){
    // remove reference to this in components
    for (auto& c : components){
        c->gameObject = nullptr;
    }
}

const glm::vec2 &GameObject::getLocalPosition() const {
    return position;
}

void GameObject::setLocalPosition(const glm::vec2 &position) {
    this->position = position;
}

float GameObject::getLocalRotation() const {
    return rotation;
}

void GameObject::setLocalRotation(float rotation) {
    this->rotation = rotation;
}

const std::vector<std::shared_ptr<Component>>& GameObject::getComponents() {
    return components;
}

GameObject::GameObject(std::string name) {
    this->name = name;
}

GameObject* GameObject::getParent() const {
    return parent;
}

void GameObject::setParent(GameObject* parent) {
    this->parent = parent;
}

const glm::vec2 GameObject::getPosition() const {
    if(parent != nullptr) {
        return parent->position + position;
    }

    return position;
}

float GameObject::getRotation() const {
    if(parent != nullptr) {
        return parent->rotation + rotation;
    }

    return rotation;
}

void GameObject::removeComponent(Component* component) {
    auto findComponent = [component](std::shared_ptr<Component> currComponent) { return currComponent.get() == component;};
    auto iter(remove_if(components.begin(), components.end(), findComponent));
    components.erase(iter);
}