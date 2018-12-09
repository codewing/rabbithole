#pragma once

#include "../engine/core/Component.hpp"
#include "../engine/core/IUpdatable.hpp"
#include "../engine/core/IInteractable.hpp"
#include "../engine/component/PhysicsComponent.hpp"

class PortalComponent : public Component, public IInteractable, public IUpdatable {

public:
	explicit PortalComponent(GameObject *gameObject);

	void setOtherPortal(PortalComponent* portal);
	PortalComponent* getOtherPortal();

    void onUpdate(float deltaTime) override;

    void onCollisionStart(IInteractable* interactable) override;  // Callback from physics engine when collision start is detected. Override when needed.
	void onCollisionEnd(IInteractable* interactable) override;    // Callback from physics engine when collision end is detected. Override when needed.

	void setPosition(glm::vec2 newPosition) override;
	void setRotation(float newAngle) override;

	glm::vec2 getPosition();
	float getRotation();

	void addTeleportedObject(IInteractable* teleportedObject);

private:

	PortalComponent* otherPortal;

	std::vector<IInteractable*> teleportedObjects;
    std::vector<PhysicsComponent*> objectsToTeleport;

};

