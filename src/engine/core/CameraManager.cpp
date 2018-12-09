//
// Created by codewing on 15.11.18.
//

#include <algorithm>
#include "CameraManager.hpp"

void CameraManager::RegisterCamera(std::string id, sre::Camera camera) {
    cameras.insert({id, camera});
}

void CameraManager::SetActiveCamera(const std::string& id) {
    activeCamera = &cameras[id];
}

void CameraManager::UnregisterCamera(const std::string& id) {
    auto element = cameras.find(id);
    cameras.erase(element);
}

sre::Camera* CameraManager::GetActiveCamera() {
    return activeCamera;
}

sre::Camera* CameraManager::GetCamera(const std::string &id) {
    auto element = cameras.find(id);
    return &(element->second);
}
