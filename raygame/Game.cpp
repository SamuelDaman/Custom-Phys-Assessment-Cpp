#include "Game.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Raylib.h"

#include "enumUtils.h"

collisionMap setupCollisionChecks()
{
	collisionMap map;

	map[(collisionPair)(ShapeType::CIRCLE | ShapeType::CIRCLE)] = checkCircleCircle;

	return map;
}

depenetrationMap setupDepenetrationFuncs()
{
	depenetrationMap map;

	map[(collisionPair)(ShapeType::CIRCLE | ShapeType::CIRCLE)] = depenetrateCircleCircle;

	return map;
}

collisionMap Game::collisionCheckers = setupCollisionChecks();
depenetrationMap Game::depenetrationFuncs = setupDepenetrationFuncs();

Game::Game()
{
	accumulatedDeltaTime = 0.0f;
	fixedTimeStep = 1.0f / 30.0f;
	srand(time(0));
}

void Game::init()
{
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
}

bool Game::tick()
{
	accumulatedDeltaTime += GetFrameTime();

	if (IsMouseButtonPressed(0))
	{
		auto cursorPos = GetMousePosition();

		PhysObject spawn;
		spawn.pos = { cursorPos.x, cursorPos.y };
		spawn.mass = (rand() % 10) + 1;
		spawn.shape.circleData.radius = spawn.mass;
		spawn.addImpulse({ 100,0 });

		PhysObjects.push_back(spawn);
	}

	return !WindowShouldClose();
}

void Game::tickPhysics()
{
	accumulatedDeltaTime -= fixedTimeStep;

	for (auto& lhs : PhysObjects)
	{
		for (auto& rhs : PhysObjects)
		{
			if (&lhs == &rhs) { continue; }

			auto * first = &lhs;
			auto * second = &rhs;

			if (static_cast<uint8_t>(lhs.shape.colliderShape) > static_cast<uint8_t>(rhs.shape.colliderShape))
			{
				first = &rhs;
				second = &lhs;
			}

			collisionPair pairType = (collisionPair)(lhs.shape.colliderShape | rhs.shape.colliderShape);

			bool collision = collisionCheckers[pairType](first->pos, first->shape, second->pos, second->shape);

			if (collision)
			{
				float pen = 0.0f;

				vec2 normal = depenetrationFuncs[pairType](first->pos, first->shape, second->pos, second->shape, pen);

				vec2 resImpulses[2];
				resolveCollision(first->pos, first->vel, first->mass, second->pos, second->vel, second->mass, 1.0f, normal, resImpulses);

				first->pos += normal * pen;
				second->pos -= normal * pen;

				first->vel = resImpulses[0];
				second->vel = resImpulses[1];
			}
		}
	}

	for (auto& obj : PhysObjects)
	{
		obj.tickPhysics(fixedTimeStep);
	}
}

bool Game::shouldTickPhysics() const
{
	return accumulatedDeltaTime >= fixedTimeStep;
}

void Game::draw() const
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (auto& obj : PhysObjects)
	{
		obj.draw();
	}

	EndDrawing();
}

void Game::exit()
{
	CloseWindow();
}
