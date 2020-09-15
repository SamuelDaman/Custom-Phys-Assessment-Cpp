#pragma once

#include <cstdint>
#include "glm/vec2.hpp"

using glm::vec2;

struct circle
{
	float radius;
};

enum class ShapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};

struct collider
{
	ShapeType colliderShape;
	union
	{
		circle circleData;
	};
};

bool checkCircleCircle(vec2 posA, circle circleA, vec2 posB, circle circleB);
bool checkCircleCircle(vec2 posA, collider circleA, vec2 posB, collider circleB);

vec2 depenetrateCircleCircle(vec2 posA, circle circleA, vec2 posB, circle circleB, float& pen);
vec2 depenetrateCircleCircle(vec2 posA, collider circleA, vec2 posB, collider circleB, float& pen);

void resolveCollision(vec2 posA, vec2 velA, float massA,
	vec2 posB, vec2 velB, float massB,
	float elasticity, vec2 colNormal, vec2* dst);