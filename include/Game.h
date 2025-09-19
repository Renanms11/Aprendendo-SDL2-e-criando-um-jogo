#ifndef _Game_
#define _Game_
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

class Game
{
    public:
        //Construtor e destrutor da class
        Game();
        ~Game();
        //função para iniciar o jogo
        bool init(const char* title, int xpos, int ypos, bool fullscreen);// varial do gameloop iniciado
        //função para renderizar o jogo
        void render();
        //função para atualizar o jogo
        void update();
        //funçao para tratar os eventos (inputs)
        void handleEvents();
        bool running(){ return isRunning; }
        // função para limpar e  terminar o jogo
        void clean();
    private:
        bool isRunning;
        SDL_Window* g_Window;
        SDL_Renderer* g_Renderer;
        int m_currentFrame;
        

};
#endif