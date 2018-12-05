//
// Created by codewing on 05.12.18.
//

#include "GameCameraController.hpp"

#include <algorithm>
#include "../engine/core/ObjectManager.hpp"

void GameCameraController::initialize() {
    ObjectManager::GetInstance()->GetCameraManager().RegisterCamera("main", sre::Camera());
    ObjectManager::GetInstance()->GetCameraManager().SetActiveCamera("main");

    cam = ObjectManager::GetInstance()->GetCameraManager().GetCamera("main");
}

void GameCameraController::focusOn(const glm::vec2& position, int distance, float time) {

    auto sanitizedDistance = std::clamp<int>(distance, minDistance, maxDistance);
    auto sanitizedTime = std::clamp<float>(time, 0, 99999999);
    auto sanitizedPositionX = std::clamp<float>(position.x, sanitizedDistance/2.0f, 2048 - sanitizedDistance/2.0f);
    auto sanitizedPositionY = std::clamp<float>(position.y, sanitizedDistance/2.0f, 2048 - sanitizedDistance/2.0f);

    sanitizedFocusOn({sanitizedPositionX, sanitizedPositionY}, sanitizedDistance, sanitizedTime);
}

void GameCameraController::update(float deltaTime) {

    if(!isAtTarget) {

        if(remainingMovementTime < deltaTime) {
            lookAtPosition(targetPosition, targetDistance);

            isAtTarget = true;
        } else {

        }
    }

}

void GameCameraController::sanitizedFocusOn(glm::vec2 position, int distance, float time) {
    targetPosition = position;
    targetDistance = distance;
    remainingMovementTime = time;

    isAtTarget = false;
}

void GameCameraController::lookAtPosition(const glm::vec2 &position, float cameraDistance) {
    glm::vec3 eye (position.x, position.y, 0);
    glm::vec3 at (position.x, position.y, -1);
    static const glm::vec3 up (0, 1, 0);
    cam->lookAt(eye, at, up);

    cam->setOrthographicProjection(cameraDistance, -1, 1);
}
