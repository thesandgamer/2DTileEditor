#pragma once
#include "raylib.h"
#include "Layer.h"
#include <stack>

using std::stack;

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual void undo() = 0;

};


class PlaceTileCommand : public Command
{
public:
	PlaceTileCommand(Layer* layer, Vector2 tilePosP) : layer_(layer), tilePos(tilePosP) {};

	virtual void execute() {
	//Lien vers le layer, et appel la fonction add tile
		layer_->AddTile(tilePos);
	}

	virtual void undo(){
		//Liens vers le layer, on remove la tile en tilepos
		layer_->RemoveTile(tilePos);
	}

private:
	Vector2 tilePos;
	Layer* layer_;

};

//Faut un truc pour faire la transition entre l'émeteur et le récépteur

class CommandManager
{
public:
	CommandManager() {};

	void CtrlZ() { commandList.top()->undo();}

	stack<Command*>* GetCommandList() { return &commandList; }

private:
	stack<Command*> commandList;

};