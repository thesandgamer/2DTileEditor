#include "UiElements.h"

UiElements::UiElements()
{
}

UiElements::UiElements( Vector2 pos, Texture2D spriteP, float widthP, float heightP) : sprite(spriteP), width(widthP), height(heightP), position(pos), drawColor(WHITE)
{
}

UiElements::UiElements(Vector2 pos, float widthP, float heightP) : width(widthP), height(heightP), position(pos), drawColor(WHITE)
{
}

UiElements::~UiElements()
{
}

void UiElements::Draw()
{
	//
	DrawRectangle(position.x, position.y, width, height, drawColor);


}

void UiElements::Update()
{
}

