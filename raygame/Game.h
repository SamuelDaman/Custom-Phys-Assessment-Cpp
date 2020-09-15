#pragma once

#include <vector>
#include <unordered_map>

#include "PhysObject.h"

using collisionPair = uint8_t;

using collisionFunc = bool(*)(glm::vec2, collider, glm::vec2, collider);
using collisionMap = std::unordered_map<collisionPair, collisionFunc>;

using depenetrationFunc = glm::vec2(*)(glm::vec2, collider, glm::vec2, collider, float&);
using depenetrationMap = std::unordered_map<collisionPair, depenetrationFunc>;

class Game 
{
	float accumulatedDeltaTime;

	std::vector<PhysObject> PhysObjects;

	static collisionMap collisionCheckers;
	static depenetrationMap depenetrationFuncs;

public:
	Game();
	float fixedTimeStep;
	void init();
	bool tick();
	void tickPhysics();
	bool shouldTickPhysics() const;
	void draw() const;
	void exit();
};