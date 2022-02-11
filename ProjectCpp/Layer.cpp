#include "Layer.h"
#include "Command.h"

Layer::Layer()
{
}

Layer::Layer(LayerType type) :layerType(type), layerUseAutoTiling(false)
{
}

Layer::Layer(LayerType type, bool useAutoTiling): layerType(type),layerUseAutoTiling(useAutoTiling)
{
}

Layer::~Layer()
{
	//buttonLayer->~Button();
	//grid.~Grid();
}

void Layer::AddTile(Vector2 tilePos)
{
	if (visible)
	{
		grid.AddTileInGrid(tilePos);
	}
}

void Layer::RemoveTile(Vector2 tilePos)
{
	if (visible)
	{
		grid.RemoveTileInGrid(tilePos);
	}
}

void Layer::Update()
{
	if (visible)
	{
		grid.Update();
	}
}

void Layer::Draw()
{
	//Ca va dessiner une ref grille de la taille de la room, avec le cell width et cell height décidé
	if (visible)
	{
		grid.Draw();
	}
}

void Layer::CreateGrid(int width, int height)
{
	grid = Grid(width, height);
	grid.SetTileMaps(tileMaps);
}

void Layer::AddButton(Vector2 pos)
{
	buttonLayer = new Button(pos, 100, 50);
}

Button* Layer::GetButton()
{
	if (buttonLayer != nullptr)
	{
		return buttonLayer;
	}
}

void Layer::RemoveButton()
{
	//delete[] buttonLayer;
	std::cout << "On remove le boutton " << std::endl;
	delete buttonLayer;
	buttonLayer->~Button();

}

void Layer::AddTileMap(string sprite)
{
	string text = "..\\Ressources\\" + sprite;
	Texture2D spr = LoadTexture(text.c_str());
	if (spr.id != 0)
	{
		tileMaps.push_back(spr);
		tileMap = spr;
	}
	else
	{
		TraceLog(LOG_DEBUG, "Image failed to import ");
	}

}

void Layer::AddTileMap(Texture2D sprite)
{
	tileMaps.push_back(sprite);
	tileMap = sprite;
}

