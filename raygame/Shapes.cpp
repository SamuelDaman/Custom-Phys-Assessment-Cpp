#include "physObject.h"

#include "raylib.h"

PhysObject::PhysObject()
{
	pos = glm::vec2{ 0,0 };
	vel = glm::vec2{ 0,0 };
	forces = glm::vec2{ 0,0 };

	mass = 1.0f;
	shape = { ShapeType::CIRCLE, circle{ 10.0f } };
}

void PhysObject::tickPhysics(float deltaTime)
{
	vel += forces * deltaTime;
	forces = { 0, 0 };

	pos += vel * deltaTime;
}

void PhysObject::draw() const
{
	switch (shape.colliderShape)
	{
	case ShapeType::NONE:
		DrawPixel((int)pos.x, (int)pos.y, RED);
		break;
	case ShapeType::CIRCLE:
		DrawCircleLines((int)pos.x, (int)pos.y, shape.circleData.radius, RED);
		break;
	case ShapeType::AABB:
		assert(false && "AABB not yet implemented -- cannot draw.");
		break;
	default:
		break;
	}
}

void PhysObject::addForce(glm::vec2 force)
{
	forces += force / mass;
}

void PhysObject::addImpulse(glm::vec2 impulse)
{
	vel += impulse / mass;
}