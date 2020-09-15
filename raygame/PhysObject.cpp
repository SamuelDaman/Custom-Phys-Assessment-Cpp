#include "shapes.h"

#include "glm/glm.hpp"

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB)
{
	float distance = glm::length(posA - posB);

	float sum = circleA.radius + circleB.radius;

	return distance < sum;
}

bool checkCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB)
{
	return checkCircleCircle(posA, circleA.circleData, posB, circleB.circleData);
}

glm::vec2 depenetrateCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB, float& pen)
{
	float dist = glm::length(posA - posB);
	float sum = circleA.radius + circleB.radius;

	pen = sum - dist;

	return glm::normalize(posA - posB);
}

glm::vec2 depenetrateCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB, float& pen)
{
	return depenetrateCircleCircle(posA, circleA.circleData, posB, circleB.circleData, pen);
}

void resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA,
	glm::vec2 posB, glm::vec2 velB, float massB,
	float elasticity, glm::vec2 colNormal, glm::vec2* dst)
{
	glm::vec2 relVel = velA - velB;

	float impulseMag = glm::dot(-(-1.0f + elasticity) * relVel, colNormal) /
		glm::dot(colNormal, colNormal * (1 / massA + 1 / massB));

	dst[0] = velA + (impulseMag / massA) * colNormal;
	dst[1] = velB - (impulseMag / massB) * colNormal;
}