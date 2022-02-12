#include "LayersManager.h"
#include "Command.h"

#include "Maths.h"
#include <string>
#include "Game.h"

int layerNumber = 0;

void LayersManager::AddLayer()
{
	LayersManager* This = &LayersManager::instance();

	layerNumber++;

	Layer newLayer = Layer(Layer::LayerType::Tiles, true);
	newLayer.CreateGrid(960, 540); //Il faudra créer une grille de la taille de la room
	newLayer.AddTileMap("TileMapV2.png");

	newLayer.AddButton(Vector2{ 100, 20.0f + (layerNumber*10 ) + (50 * layerNumber) });
	This->actualLayer++;
	newLayer.GetButton()->functPrtInt = &LayersManager::SelectLayer;
	newLayer.GetButton()->value = This->actualLayer;

	This->layers.push_back(newLayer);
	This->GoToLayer(This->actualLayer);


}

void LayersManager::RemoveLayer()
{
	layers[actualLayer - 1].RemoveButton();
	layers[actualLayer - 1].~Layer();
	actualLayer--;
	layerNumber--;
	GoToLayer(actualLayer);
}

void LayersManager::AddTileMapToActualLayer(string tileSet)
{
	string sprite = "../../Resources/" + tileSet; //Va chercher le tileSet
	layers[actualLayer-1].AddTileMap(LoadTexture(sprite.c_str()));
}

void LayersManager::SelectLayer(int layer)
{
	LayersManager* This = &LayersManager::instance();

	This->actualLayer = layer;
	This->GoToLayer(This->actualLayer);
}

void LayersManager::ProcessInputs()
{
	//Calcul la position de la souris
	Vector2 mouse = GetMousePosition();
	Vector2 mousePosInGrid = { 0 };
	

	//Check quand on clique

	if (!layers.empty())
	{
		mousePosInGrid = layers[actualLayer - 1].GetGrid().CalculatePositionInGrid(mouse);

		bool InGrid = (mousePosInGrid.x >= 0 && mousePosInGrid.x <= layers[actualLayer - 1].GetGrid().GridSize().x)
			&& (mousePosInGrid.y >= 0 && mousePosInGrid.y <= layers[actualLayer - 1].GetGrid().GridSize().y);

		if (InGrid) // layers[actualLayer - 1].GetGrid().GridSize().x) //Check si est dans la grille
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				//layers[actualLayer - 1].AddTile(mousePosInGrid);
				PlaceTileCommand* command = new PlaceTileCommand(&layers[actualLayer - 1], mousePosInGrid);
				command->execute();
				Game::instance().GetCommandManager().GetCommandList()->push(command);

			}
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
			{
				layers[actualLayer - 1].RemoveTile(mousePosInGrid);

			}
		}
		//Check si la position de la souris et dans la position du layer
	}
	
	if (IsKeyPressed(KEY_DELETE))
	{
		RemoveLayer();
	}
	DrawText(("Mouse: " + to_string(mouse.x) + " : " + to_string(mouse.y)).c_str(), 40, 40, 10, WHITE);
	DrawText(("MouseInGrid: " + to_string(mousePosInGrid.x) + " : " + to_string(mousePosInGrid.y)).c_str(), 40, 70, 10, WHITE);

}




void LayersManager::Update()
{
	for (Layer layer : layers)
	{
		
		if (layer.GetButton() != nullptr) //Check si le boutton existe
		{
			layer.GetButton()->Update();

		}

		layer.Update();
	}
}

void LayersManager::Draw()
{
	for (Layer layer : layers)
	{
		if (layer.GetButton() != nullptr) //Check si le boutton existe
		{
			layer.GetButton()->Draw();
		}

		layer.Draw();
	}

	string text = "Actual Layer: " + std::to_string(actualLayer);
	DrawText(text.c_str(), 10, 10, 10, WHITE);
}



void LayersManager::GoToLayer(int layer)
{

}
