#pragma once

#include <cstdint>
#include "glm/vec2.hpp"

struct circle
{
	float radius;
};

enum class shapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};

struct collider
{
	shapeType colliderShape;
	union
	{
		circle circleData;
	};
};

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);
bool checkCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB);

glm::vec2 depenetrateCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB, float& pen);
glm::vec2 depenetrateCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB, float& pen);

void resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA,
	glm::vec2 posB, glm::vec2 velB, float massB,
	float elasticity, glm::vec2 colNormal, glm::vec2* dst);