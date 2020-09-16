#include "shapes.h"

#include "glm/glm.hpp"

bool checkCircleCircle(vec2 posA, circle circleA, vec2 posB, circle circleB)
{
	float distance = glm::length(posA - posB);

	float sum = circleA.radius + circleB.radius;

	return distance < sum;
}

bool checkCircleCircle(vec2 posA, collider circleA, vec2 posB, collider circleB)
{
	return checkCircleCircle(posA, circleA.circleData, posB, circleB.circleData);
}

bool checkBoxBox(vec2 posA, box boxA, vec2 posB, box boxB)
{
	vec2 minA = posA - boxA.bounds;
	vec2 maxA = posA + boxA.bounds;
	vec2 minB = posB - boxB.bounds;
	vec2 maxB = posB + boxB.bounds;

	return !(maxA.x < minB.x || maxA.y < minB.y || minA.x > maxB.x || minA.y > maxB.y);
}

bool checkBoxBox(vec2 posA, collider boxA, vec2 posB, collider boxB)
{
	return checkBoxBox(posA, boxA.boxData, posB, boxB.boxData);
}

vec2 depenetrateCircleCircle(vec2 posA, circle circleA, vec2 posB, circle circleB, float& pen)
{
	float dist = glm::length(posA - posB);
	float sum = circleA.radius + circleB.radius;

	pen = sum - dist;

	return glm::normalize(posA - posB);
}

vec2 depenetrateCircleCircle(vec2 posA, collider circleA, vec2 posB, collider circleB, float& pen)
{
	return depenetrateCircleCircle(posA, circleA.circleData, posB, circleB.circleData, pen);
}

vec2 depenetrateBoxBox(vec2 posA, box boxA, vec2 posB, box boxB, float& pen)
{
	float distX = posA.x - posB.x;
	float distY = posA.y - posB.y;
	float sumX = boxA.bounds.x + boxB.bounds.x;
	float sumY = boxA.bounds.y + boxB.bounds.y;

	if (sumX - distX < sumY - distY)
	{
		pen = (sumX - distX);
	}
	else
	{
		pen = (sumY - distY);
	}
	return glm::normalize(posA - posB);
}

vec2 depenetrateBoxBox(vec2 posA, collider boxA, vec2 posB, collider boxB, float& pen)
{
	return depenetrateBoxBox(posA, boxA.boxData, posB, boxB.boxData, pen);
}

void resolveCollision(vec2 posA, vec2 velA, float massA,
	vec2 posB, vec2 velB, float massB,
	float elasticity, vec2 colNormal, vec2* dst)
{
	vec2 relVel = velA - velB;

	float impulseMag = glm::dot(-(-1.0f + elasticity) * relVel, colNormal) / glm::dot(colNormal, colNormal * (1 / massA + 1 / massB));

	dst[0] = velA + (impulseMag / massA) * colNormal;
	dst[1] = velB - (impulseMag / massB) * colNormal;
}