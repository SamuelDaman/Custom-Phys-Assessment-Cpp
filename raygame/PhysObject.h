#pragma once

#include "glm/glm.hpp"

#include "shapes.h"

class physObject
{
	glm::vec2 forces;

public:

	glm::vec2 pos;
	glm::vec2 vel;
	float mass;
	collider shape;
	physObject();
	void tickPhysics(float deltaTime);
	void draw() const;
	void addForce(glm::vec2 force);
	void addImpulse(glm::vec2 impulse);
	void addAccel(glm::vec2 accel);
	void addVelocityChange(glm::vec2 velChng);
};