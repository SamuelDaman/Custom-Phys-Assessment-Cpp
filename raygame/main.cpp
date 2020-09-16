/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "Game.h"

#include "glm/glm.hpp"

int main()
{
	Game app;

	app.init();
	app.fixedTimeStep = 1.0f / 30.0f;

	bool shouldRun = true;

	// Main game loop
	while (shouldRun)    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		shouldRun = app.tick();

		while (app.shouldTickPhysics())
		{
			app.tickPhysics();
		}

		// Draw
		//----------------------------------------------------------------------------------
		app.draw();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	app.exit();
	//--------------------------------------------------------------------------------------

	return 0;
}