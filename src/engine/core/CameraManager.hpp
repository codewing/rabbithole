//
// Created by codewing on 15.11.18.
//


#pragma once

#include <string>
#include <map>
#include <sre/Camera.hpp>

class CameraManager {

private:
    std::map<std::string, sre::Camera> cameras;
    sre::Camera* activeCamera;

public:
    sre::Camera* GetCamera(const std::string &id);

    void SetActiveCamera(const std::string& id);
    sre::Camera* GetActiveCamera();

    void RegisterCamera(std::string id, sre::Camera camera);
    void UnregisterCamera(const std::string& id);
};


