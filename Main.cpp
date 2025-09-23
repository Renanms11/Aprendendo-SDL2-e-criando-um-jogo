#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Game* g_game = 0;


int main(int argc , char* argv[]){

    if(TheGame::Instance()->init("Argonaut",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,false)){
        while(TheGame::Instance()->running()){
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();
            SDL_Delay(100);
        }
    }else{
        std::cout << "Não foi possivel iniciar o Jogo" << std::endl;
        return -1;
    }

    TheGame::Instance()->clean();
    
    return 0;
}