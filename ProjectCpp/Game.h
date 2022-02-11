#pragma once
#include "raylib.h"
#include "LayersManager.h"
#include <string>

#include "Button.h"
#include "Command.h"

using std::string;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : RoomWidth(960), RoomHeight(540) {};


public:
	void Initialise();
	void Loop();
	void Close();

	//Game Specific
	CommandManager GetCommandManager() { return commandManager; }


private:
	void ProcessInput();
	void Update();
	void Draw();

	//
//Setup la taille de l'écran
	int const RoomWidth = 960;
	int const RoomHeight = 540;

	CommandManager commandManager;



};
