#pragma once

class Game 
{
	float accumulatedDeltaTime;

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