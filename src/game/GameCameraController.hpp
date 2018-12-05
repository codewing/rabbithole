//
// Created by codewing on 05.12.18.
//

#pragma once

#include <sre/Camera.hpp>

class GameCameraController {

public:

    GameCameraController() = default;
    void initialize();

    void update(float deltaTime);

    void focusOn(const glm::vec2& position, int distance, float time);

private:
    sre::Camera* cam;

    bool isAtTarget = true;
    glm::vec2 targetPosition = {0, 0};
    float targetDistance = 500;
    float remainingMovementTime = 0;

    static constexpr int minDistance = 500;
    static constexpr int maxDistance = 700;

    void sanitizedFocusOn(glm::vec2 position, int distance, float time);
    void lookAtPosition(const glm::vec2& position, float cameraDistance);
};

