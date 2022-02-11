#include "Game.h"

Button* addLayerButton;


void Game::Initialise()
{
    //Créer un écran et on met les fps à 60
    string windowName = "Editor";
    InitWindow(RoomWidth, RoomHeight, windowName.c_str());
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetWindowMinSize(1920, 1080);

    //ToggleFullscreen();
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    //Ajouter les boutons d'éditeur
    Vector2 pos1 = { 20,400 };
    addLayerButton = new Button(pos1, 40.0f, 40.0f);

    addLayerButton->functPrt = &LayersManager::instance().AddLayer;

    

}

void Game::Loop()
{
    ProcessInput();
    Update();
    Draw();
}

void Game::Close()
{
    CloseWindow();
}

void Game::ProcessInput()
{
   LayersManager::instance().ProcessInputs();
}

void Game::Update()
{
    LayersManager::instance().Update();

    addLayerButton->Update();
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    LayersManager::instance().Draw();

    addLayerButton->Draw();

    EndDrawing();
}
