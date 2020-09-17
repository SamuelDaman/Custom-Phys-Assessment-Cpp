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
	map[(collisionPair)(ShapeType::CIRCLE | ShapeType::AABB)] = checkCircleBox;
	map[(collisionPair)(ShapeType::AABB | ShapeType::AABB)] = checkBoxBox;

	return map;
}

depenetrationMap setupDepenetrationFuncs()
{
	depenetrationMap map;

	map[(collisionPair)(ShapeType::CIRCLE | ShapeType::CIRCLE)] = depenetrateCircleCircle;
	map[(collisionPair)(ShapeType::CIRCLE | ShapeType::AABB)] = depenetrateCircleBox;
	map[(collisionPair)(ShapeType::AABB | ShapeType::AABB)] = depenetrateBoxBox;

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
		spawn.mass = (rand() % 10) + 5;

		if (rand() % 2 == 0)
		{
			spawn.shape.circleData.radius = spawn.mass + 4;
		}
		else
		{
			spawn.shape.colliderShape = ShapeType::AABB;
			spawn.shape.boxData.bounds = { spawn.mass + 4, spawn.mass + 4 };
		}
		spawn.addImpulse({ (rand() % 501) - 250, (rand() % 501) - 250 });

		PhysObjects.push_back(spawn);
	}

	if (IsMouseButtonPressed(1))
	{
		auto cursorPos = GetMousePosition();

		for (auto& obj : PhysObjects)
		{
			auto * object = &obj;
			if (glm::length(vec2(cursorPos.x, cursorPos.y) - object->pos) < 100)
			{
				obj.addImpulse(glm::normalize(object->pos - vec2(cursorPos.x, cursorPos.y)) * 5000.0f);
			}
		}
	}

	return !WindowShouldClose();
}

void Game::tickPhysics()
{
	accumulatedDeltaTime -= fixedTimeStep;

	for (auto& obj : PhysObjects)
	{
		obj.addAccel(vec2(0, 98));
		glm::clamp(obj.vel.x, -10.0f, 10.0f);
		glm::clamp(obj.vel.y, -10.0f, 10.0f);
	}

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

	for (auto& obj : PhysObjects)
	{
		auto * object = &obj;
		int scrWidth = GetScreenWidth();
		int scrHeight = GetScreenHeight();
		if (object->pos.x < -10)
		{
			object->pos.x = scrWidth + 10;
		}
		if (object->pos.x > scrWidth + 10)
		{
			object->pos.x = -10;
		}
		if (object->pos.y < -10)
		{
			object->pos.y = scrHeight + 10;
		}
		if (object->pos.y > scrHeight + 10)
		{
			object->pos.y = -10;
		}
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
