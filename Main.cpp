#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

//  Valores de largura e altura da tela
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Uint32 frameStart, frameTime;

// Variáveis de controle do loop, Qtd frame, e o tempo de delay
const int FPS = 60;
const int DELAY_TIME = 1000.F /60;

Game* g_game = 0;


int main(int argc , char* argv[]){

    if(TheGame::Instance()->init("Argonaut",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,false)){
        while(TheGame::Instance()->running()){
            
            frameStart = SDL_GetTicks();
            
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;
            if(frameTime < DELAY_TIME){
                SDL_Delay((int) (DELAY_TIME - frameStart));
            }
            
        }
    }else{
        std::cout << "Não foi possivel iniciar o Jogo" << std::endl;
        return -1;
    }

    TheGame::Instance()->clean();
    
    return 0;
}