#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IUpdatable.hpp"
#include "../engine/core/IInteractable.hpp"
#include "../engine/component/PhysicsComponent.hpp"

class PortalComponent : public Component, public IInteractable {

public:
	explicit PortalComponent(GameObject *gameObject);

	void setOtherPortal(std::shared_ptr<GameObject> gameObject);
	std::shared_ptr<GameObject> getOtherPortal();

	void onCollisionStart(IInteractable* interactable) override;  // Callback from physics engine when collision start is detected. Override when needed.
	void onCollisionEnd(IInteractable* interactable) override;    // Callback from physics engine when collision end is detected. Override when needed.

	void setPosition(glm::vec2 newPosition) override;
	void setRotation(float newAngle) override;

private:

	std::shared_ptr<GameObject> otherPortal;

};

