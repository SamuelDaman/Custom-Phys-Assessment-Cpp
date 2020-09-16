#pragma once

#include "glm/glm.hpp"

#include "shapes.h"

class PhysObject
{
	vec2 forces;

public:

	vec2 pos;
	vec2 vel;
	float mass;
	collider shape;
	PhysObject();
	void tickPhysics(float deltaTime);
	void draw() const;
	void addForce(vec2 force);
	void addImpulse(vec2 impulse);
	void addAccel(vec2 accel);
	void addVelocityChange(vec2 velChng);
};