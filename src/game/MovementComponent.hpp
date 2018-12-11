//
// Created by codewing on 28.11.18.
//

#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IUpdatable.hpp"
#include "../engine/core/IInputable.hpp"

#include "RabbitPhysicsComponent.hpp"

class SpriteComponent;

class MovementComponent : public Component, public IUpdatable, public IInputable {

public:
    explicit MovementComponent(GameObject *gameObject);

    void onUpdate(float deltaTime) override;
    bool onKeyEvent(SDL_Event &event) override;
	void setGrounded(bool value);
    bool onControllerEvent(SDL_Event &event) override;

    void setupControllerInput(int gamepadID);
    void setupSprites(SpriteComponent* spriteComponent, std::vector<sre::Sprite> idleSprites, std::vector<sre::Sprite> movementSprites);

    void setIsAiming(bool isAiming);
    void setIsFlippedDueToAiming(bool isFlippedDueToAiming);

    bool isIsFlippedDueToMovement() const;

    virtual ~MovementComponent();

private:

    std::shared_ptr<RabbitPhysicsComponent> physicsComponent = nullptr;

    float moveRight = 0;
    bool jump = false;
	bool isGrounded = false;
	bool isAiming = false;
	bool isFlippedDueToAiming = false;

	SpriteComponent* spriteComponent;
	std::vector<sre::Sprite> idleSprites;
	std::vector<sre::Sprite> movementSprites;
	bool isMoving = false;
	bool isFlippedDueToMovement = false;
	int currentSpriteIndex = 0;
	float currentTimeFrame = 0;
    static constexpr float idleTimeFrame = 0.3;
    static constexpr float movementTimeFrame = 0.1;

    int gamepadID = -1;
    SDL_GameController* controllerHandle = nullptr;
    static constexpr float axisValueMax = 32768;
    static constexpr float controllerDeadzone = 0.02;
};
