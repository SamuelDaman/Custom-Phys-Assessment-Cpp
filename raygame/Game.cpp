#include "Game.h"

#include "Raylib.h"

#include <iostream>

Game::Game()
{
	accumulatedDeltaTime = 0.0f;
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

	std::cout << "Do Update" << std::endl;

	return !WindowShouldClose();
}

void Game::tickPhysics()
{
	accumulatedDeltaTime -= fixedTimeStep;

	std::cout << "Do Physics" << std::endl;
}

bool Game::shouldTickPhysics() const
{
	return accumulatedDeltaTime >= fixedTimeStep;
}

void Game::draw() const
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	

	EndDrawing();
}

void Game::exit()
{
	CloseWindow();
}
