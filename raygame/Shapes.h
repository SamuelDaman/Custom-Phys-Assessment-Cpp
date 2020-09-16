#pragma once

#include <cstdint>
#include "glm/vec2.hpp"

using glm::vec2;

struct circle
{
	float radius;
};

struct box
{
	vec2 bounds;
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
		box boxData;
	};
};

bool checkCircleCircle(vec2 posA, circle circleA, vec2 posB, circle circleB);
bool checkCircleCircle(vec2 posA, collider circleA, vec2 posB, collider circleB);

bool checkBoxBox(vec2 posA, box boxA, vec2 posB, box boxB);
bool checkBoxBox(vec2 posA, collider boxA, vec2 posB, collider boxB);

vec2 depenetrateCircleCircle(vec2 posA, circle circleA, vec2 posB, circle circleB, float& pen);
vec2 depenetrateCircleCircle(vec2 posA, collider circleA, vec2 posB, collider circleB, float& pen);

vec2 depenetrateBoxBox(vec2 posA, box boxA, vec2 posB, box boxB, float& pen);
vec2 depenetrateBoxBox(vec2 posA, collider boxA, vec2 posB, collider boxB, float& pen);

void resolveCollision(vec2 posA, vec2 velA, float massA, vec2 posB, vec2 velB, float massB, float elasticity, vec2 colNormal, vec2 * dst);