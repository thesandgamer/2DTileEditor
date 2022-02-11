#include <iostream>

#include "Game.h"


int main(int argc, char* argv[])
{

   Game::instance().Initialise();


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
       Game::instance().Loop();
 
    }

    Game::instance().Close();

    return 0;

}

