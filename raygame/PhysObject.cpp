#include "physObject.h"

#include "raylib.h"

PhysObject::PhysObject()
{
	pos = vec2{ 0,0 };
	vel = vec2{ 0,0 };
	forces = vec2{ 0,0 };

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
		DrawRectangleLines((int)pos.x - shape.boxData.bounds.x, (int)pos.y - shape.boxData.bounds.y, shape.boxData.bounds.x * 2, shape.boxData.bounds.y * 2, RED);
		break;
	default:
		break;
	}
}

void PhysObject::addForce(vec2 force)
{
	forces += force / mass;
}

void PhysObject::addImpulse(vec2 impulse)
{
	vel += impulse / mass;
}

void PhysObject::addAccel(vec2 accel)
{
	forces += accel;
}

void PhysObject::addVelocityChange(vec2 velChng)
{
	vel += velChng;
}