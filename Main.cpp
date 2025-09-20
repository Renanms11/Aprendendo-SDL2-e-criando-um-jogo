#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"



Game* g_game = 0;


int main(int argc , char* argv[]){

    int flags {0};

    std::string gameName = "Argonaut";
    g_game = new Game();
    g_game->init(gameName.c_str(),100,100,false);

    while(g_game -> running()){ 
        g_game -> handleEvents();
        g_game -> update();
        g_game -> render();
        SDL_Delay(10);
    }
    delete g_game; // destruindo o  game
    return 0;
}