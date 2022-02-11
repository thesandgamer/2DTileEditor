#include "Grid.h"
#include <iostream>

#include "Tile.h"

Grid::Grid()
{
}



Grid::Grid(int width, int height): gridWidth(width),gridHeight(height), cellWidth(32),cellHeight(32), tileMap(nullptr)
{
    ResizeGrid(Vector2{ (float)width,(float)height});
    startPos = Vector2{ 400,400 };
    gridColor = ColorFromHSV(GetRandomValue(0, 255), GetRandomValue(0, 255), 1);
}

Grid::~Grid()
{
}




void Grid::Draw()
{
    if (!grid.empty())
    {
        //Draw les tiles présentes
        for (int i = 0; i < nbOfTilesWidth; i++)
        {
            for (int j = 0; j < nbOfTilesHeight; j++)
            {
                if (grid[i][j] != nullptr)
                {
                    grid[i][j]->Draw();

                }
                else
                {
                    Rectangle rec = Rectangle{ startPos.x + (float)i * cellWidth, startPos.y + (float)j * cellHeight,
                        (float)cellWidth, (float)cellHeight };
                    DrawRectangleLinesEx(rec, 1, WHITE);
                }
            }
        }
    }

}

void Grid::Update()
{
}

void Grid::SetCellSize(Vector2 size)
{
}

void Grid::AddTileInGrid(Vector2 pos)
{
    //if (tileMaps->empty()) { TraceLog(LOG_DEBUG, "Tilemaps not found "); }
    if (tileMap != nullptr) { TraceLog(LOG_DEBUG, "Tilemap not found "); }
    //Check si là où on veut poserest dans la taille de la grid
    //if ( (pos.y > grid[0].size() && pos.y > 0 ) && (pos.y > grid[0].size() && pos.y > 0) )
    if (!grid.empty())
    {
        grid[pos.x][pos.y] = new Tile( Vector2{ pos.x, pos.y }, Vector2{(float)cellWidth,(float)cellHeight}, tileMap );
        grid[pos.x][pos.y]->gridAnchorStartPos = startPos;
        CheckAndReplaceAroundTile(pos);
        grid[pos.x][pos.y]->colorPreview = gridColor;
    }

}

void Grid::RemoveTileInGrid(Vector2 pos)
{
    if (grid[pos.x][pos.y])
    {
        grid[pos.x][pos.y]->~Tile();
        grid[pos.x][pos.y] = NULL;
        CheckAndReplaceAroundTile(pos);
    }

}


Vector2 Grid::CalculatePositionInGrid(const Vector2& pos)
{
    // cout << "Position de la souris: " << mousePos.x << " : " << mousePos.y << endl;
    float newPosX = pos.x;
    float newPosY = pos.y;
    float mouseInGridX = floor(newPosX / cellWidth - startPos.x / cellWidth); //- floor(startPos.x / cellWidth);
    float mouseInGridY = floor(newPosY / cellHeight - startPos.y / cellWidth); //- floor(startPos.y / cellWidth);

    Vector2 posInGrid = Vector2{ mouseInGridX,mouseInGridY };

    return posInGrid;
}


uint8_t Grid::CheckTilesAround(Vector2 tilePos)
{
    //On va check si autour de la position données il y a d'autres tiles
#pragma region CheckTiles

    int posX = tilePos.x; // Position en X de la tile
    int posY = tilePos.y; // Position en Y de la tile

    int North = tilePos.y - 1; // La position au nord de la tile
    int South = tilePos.y + 1; // La position au sud de la tile

    int East = tilePos.x + 1; // La position à l'est de la tile
    int West = tilePos.x - 1; // La position à l'ouest de la tle

    uint8_t value = 0; // Setup la value qui va nous permettre de savoir à la fin ce qui entour la tile

    auto iter = grid.begin();

    //Haut
    if (grid[West][North] != 0  ) //Si la case du tableau en haut à gauche n'est pas vide
    {
        if ((grid[posX][North] != 0) && (grid[West][posY] != 0))
        {
            value |= TileAround::UPLEFT;
        }
    }
    if (grid[posX][North] != 0) //Si la case du tableau en haut n'est pas vide
    {
        value |= TileAround::UP;
    }
    if (grid[East][North] != 0)//Si la case du tableau en haut à droite n'est pas vide
    {
        if ((grid[posX][North] != 0) && (grid[East][posY] != 0))
        {
            value |= TileAround::UPRIGHT ;
        }
    }

    //Bas
    if (grid[West][South] != 0) //Si la case du tableau en bas à gauche n'est pas vide
    {
        if ((grid[posX][South] != 0) && (grid[West][posY] != 0))
        {
            value |= TileAround::DOWNLEFT;
        }
    }
    if (grid[posX][South] != 0) //Si la case du tableau en bas n'est pas vide
    {
        value |= TileAround::DOWN;
    }
    if (grid[East][South] != 0) //Si la case du tableau en bas à droite n'est pas vide
    {
        if ((grid[posX][South] != 0) && (grid[East][posY] != 0))
        {
            value |= TileAround::DOWNRIGHT;
        }
    }

    //Gauche
    if (grid[West][posY] != 0) //Si la case du tableau à gauche n'est pas vide
    {
        value |= TileAround::LEFT;

    }

    //Droit
    if (grid[East][posY] != 0) //Si la case du tableau à droite n'est pas vide
    {
        value |= TileAround::RIGHT;

    }
    std::cout << "Value: " << value << std::endl;

    value = Conversion(value); //Convertie la valeur pour en sorte que ça aille de 1 à 47

    return value;
#pragma endregion
}


void Grid::ChangeSpriteOfTile(Vector2 tilePos)
{

    grid[tilePos.x][tilePos.y]->ChangeSprite(CheckTilesAround(tilePos));
 
}

void Grid::ResizeGrid(Vector2 gridSize)
{
    //Resetup la taille de la grille
    gridWidth = gridSize.x;
    gridHeight = gridSize.y;

    //Resetup le nombre de lignes et collones
    nbOfTilesWidth = gridWidth / cellWidth;
    nbOfTilesHeight = gridHeight / cellHeight;

    //Resize la grille
    grid.resize(nbOfTilesWidth);
    for (size_t i = 0; i < grid.size(); i++)
    {
        grid[i].resize(nbOfTilesHeight);
    }
}

void Grid::ChangeCellWithAndHeight(Vector2 newSize)
{
    cellWidth = newSize.x;
    cellHeight = newSize.y;

    //Resetup le nombre de lignes et collones
    nbOfTilesWidth = gridWidth / cellWidth;
    nbOfTilesHeight = gridHeight / cellHeight;
}


/// <summary>
/// Converti une valeur entre 0 et 255 par une valeur entre 0 et 46 pour fit avec la tilemap
/// </summary>
/// <param name="arg"></param>
/// <returns></returns>
int Grid::Conversion(int arg)
{
    //Converti la valeur données pour resortir une valeur comprise entre 1 et 47
    switch (arg)
    {
    case 0:		return 0; break;
    case 2:		return 1; break;
    case 8:		return 2; break;
    case 10:	return 3; break;
    case 11:	return 4; break;
    case 16:	return 5; break;
    case 18:	return 6; break;
    case 22:	return 7; break;
    case 24:	return 8; break;
    case 26:	return 9; break;
    case 27:	return 10; break;
    case 30:	return 11; break;
    case 31:	return 12; break;
    case 64:	return 13; break;
    case 66:	return 14; break;
    case 72:	return 15; break;
    case 74:	return 16; break;
    case 75:	return 17; break;
    case 80:	return 18; break;
    case 82:	return 19; break;
    case 86:	return 20; break;
    case 88:	return 21; break;
    case 90:	return 22; break;
    case 91:	return 23; break;
    case 94:	return 24; break;
    case 95:	return 25; break;
    case 104:	return 26; break;
    case 106:	return 27; break;
    case 107:	return 28; break;
    case 120:	return 29; break;
    case 122:	return 30; break;
    case 123:	return 31; break;
    case 126:	return 32; break;
    case 127:	return 33; break;
    case 208:	return 34; break;
    case 210:	return 35; break;
    case 214:	return 36; break;
    case 216:	return 37; break;
    case 218:	return 38; break;
    case 219:	return 39; break;
    case 222:	return 40; break;
    case 223:	return 41; break;
    case 248:	return 42; break;
    case 250:	return 43; break;
    case 251:	return 44; break;
    case 254:	return 45; break;
    case 255:	return 46; break;
    default: return arg;
    }
}

void Grid::CheckAndReplaceAllTiles()
{
    for (int x = 0; x < nbOfTilesWidth; x++)
    {
        for (int y = 0; y < nbOfTilesHeight; y++)
        {
            grid[x][y]->ChangeSprite(CheckTilesAround(Vector2{(float)x,(float)y}));
        }
    }

}


/// <summary>
/// Check les tiles autour de la tile donnée, et changer son sprite en fonction de ce qu'il y a atour
/// </summary>
/// <param name="tilePos"></param>
void Grid::CheckAndReplaceAroundTile(Vector2 tilePos)
{
    //Check 9 tiles
    for (int x = tilePos.x -1; x < tilePos.x+2; x++) 
    {
        for (int y = tilePos.y-1; y < tilePos.y+2; y++)
        {
            //Check si x > 0 < grid with
            if (x >= 0 && x <= gridWidth)
            {
                if(y >= 0 && y <= gridHeight)
                {
                    if (grid[x][y] != nullptr) //y'a un bug car si on est au bord on va essayer d'accéder à des tiles hors
                    {
                        grid[x][y]->ChangeSprite(CheckTilesAround(Vector2{ (float)x,(float)y }));

                    }
                }

            }

        }
    }
}

