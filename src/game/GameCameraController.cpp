//
// Created by codewing on 05.12.18.
//

#include "GameCameraController.hpp"

#include <algorithm>
#include "../engine/core/ObjectManager.hpp"
#include <sre/Renderer.hpp>

void GameCameraController::initialize() {
    ObjectManager::GetInstance()->GetCameraManager().RegisterCamera("main", sre::Camera());
    ObjectManager::GetInstance()->GetCameraManager().SetActiveCamera("main");

    cam = ObjectManager::GetInstance()->GetCameraManager().GetCamera("main");
}

void GameCameraController::focusOn(const glm::vec2& position, int distance, float time) {
    float aspectRatio = getAspectRatio();

    auto sanitizedDistance = std::clamp<int>(distance, minDistance, maxDistance);
    auto sanitizedTime = std::clamp<float>(time, 0, 99999999);
    auto sanitizedPositionX = std::clamp<float>(position.x, sanitizedDistance * aspectRatio - 1000, 4096 - sanitizedDistance* aspectRatio);
    auto sanitizedPositionY = std::clamp<float>(position.y, sanitizedDistance - 1000, 4096 - sanitizedDistance);

    sanitizedFocusOn({sanitizedPositionX, sanitizedPositionY}, sanitizedDistance, sanitizedTime);
}

void GameCameraController::update(float deltaTime) {

    if(!isAtTarget) {
        float remainingAnimationDuration = animationDuration - animationTime;

        if(remainingAnimationDuration < deltaTime) {
            lookAtPosition(targetPosition, targetDistance);

            isAtTarget = true;
        } else {

            animationTime += deltaTime;
            float animationPercentage = std::clamp<float>(animationTime/animationDuration, 0.0f, 1.0f);
            float t = glm::smoothstep(0.0f, 1.0f, animationPercentage);

            glm::vec2 position = glm::mix(startPosition, targetPosition, t);
            currentDistance = glm::mix(startDistance, targetDistance, t);

            lookAtPosition(position, currentDistance);
        }
    }

}

void GameCameraController::sanitizedFocusOn(glm::vec2 position, int distance, float time) {
    targetPosition = position;
    targetDistance = distance;

    startPosition = cam->getPosition();
    targetDistance = currentDistance;

    animationTime = 0;
    animationDuration = time;

    isAtTarget = false;
}

void GameCameraController::lookAtPosition(const glm::vec2 &position, float cameraDistance) {
    glm::vec3 eye (position.x, position.y, 0);
    glm::vec3 at (position.x, position.y, -1);
    cam->lookAt(eye, at, up);

    cam->setOrthographicProjection(cameraDistance, -1, 1);
}

float GameCameraController::getAspectRatio() {
    float aspectY = sre::Renderer::instance->getWindowSize().y;
    float aspectX = sre::Renderer::instance->getWindowSize().x;

    return aspectX / aspectY;
}
