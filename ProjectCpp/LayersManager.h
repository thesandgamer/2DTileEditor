#pragma once
#include "raylib.h"
#include "Grid.h"
#include "Layer.h"

#include <string>
using std::to_string;

class LayersManager
{
	//Ca va gérer tous les layers(singleton?)
	//Va stoquer tous les layers

//Pour que se soit un singleton
public:
	static LayersManager& instance()
	{
		static LayersManager inst;
		return inst;
	}
	LayersManager(const LayersManager&) = delete;
	LayersManager& operator=(const LayersManager&) = delete;
	LayersManager(LayersManager&&) = delete;
	LayersManager& operator=(LayersManager&&) = delete;
private:
	LayersManager() : actualLayer(0), virtualMousePos({ 0 }) {};



public:
	//Fonction d'ajout de layer
	static void AddLayer();
	void RemoveLayer();


	//Fonction set les tilesSet/tilemap du layer
	void AddTileMapToActualLayer(string tileSet);

	//Get le current layer
	static void SelectLayer(int layer);
	int GetCurrentLayer() { return actualLayer; }

	//Gérer les inputs
	void ProcessInputs();
	//Inputs de la position de la souris
	//Input de click de la souris

	void Update();
	void Draw();


	//UiManger


private:

	void GoToLayer(int layer);

	vector<Layer> layers;
	int actualLayer ;

	Vector2 virtualMousePos = {0};


};

//Faire en sorte qu'aucun layer ne puisse être séléctionné

//Si on voit la grille de référence en fond(sélecte un layer on on active le draw de refgrid)
//Rajouter la possibilité d'avoir des layers d'UI