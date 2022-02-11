#pragma once
#include "raylib.h"
#include <vector>
#include <string>
using std::string;

class Tile
{
public:
	Tile();
	Tile(Vector2 posP, Vector2 sizeP, Texture2D* spriteP);
	Tile(Vector2 posP, Vector2 sizeP);
	~Tile();

	void Update();
	void Draw();

	const Vector2 getPosition() const { return pos; }

	void ChangeSprite(int value);

	Vector2 gridAnchorStartPos;
	Color colorPreview = PURPLE;

private:
	Vector2 pos;

	Vector2 size;

	Texture2D* sprite;

	Rectangle spriteEmplacement;

	int valueForTest;


};

