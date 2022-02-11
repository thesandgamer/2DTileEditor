#pragma once
#include "Button.h"
#include <vector>
using std::vector;


class LayerButton
{
public:
	LayerButton();
	~LayerButton();
	LayerButton(Vector2 pos);
	LayerButton(Vector2 pos,vector<Texture2D> sprites);


private:
	Button selectButton;
	Button showHideButton;

};

