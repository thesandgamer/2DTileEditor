#pragma once
#include "raylib.h"

class UiElements
{
public:
	UiElements();
	UiElements(Vector2 pos,Texture2D spriteP,float widthP,float heightP);
	UiElements(Vector2 pos,float widthP, float heightP);
	~UiElements();


	void Draw();
	virtual void Update();



protected:
	Vector2 position;
	float width;
	float height;
	Texture2D sprite;
	Color drawColor;


};

