#pragma once

#include <vector>
#include <unordered_map>

#include "PhysObject.h"

using collisionPair = uint8_t;

using collisionFunc = bool(*)(vec2, collider, vec2, collider);
using collisionMap = std::unordered_map<collisionPair, collisionFunc>;

using depenetrationFunc = vec2(*)(vec2, collider, vec2, collider, float&);
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