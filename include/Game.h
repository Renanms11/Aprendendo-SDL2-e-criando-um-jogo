#ifndef _Game_
#define _Game_
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
    public:
        
        static Game* Instance();
        //função para iniciar o jogo
        bool init(const char* title, int xpos, int ypos, bool fullscreen);// varial do gameloop iniciado
        //função para renderizar o jogo
        void render();
        //funçao para tratar os eventos (inputs)
        void handleEvents();
        //função para atualizar o jogo
        void update();
        // Função para ver se o jogo esta rodando
        bool running(){ return isRunning; }
        // função para limpar e  terminar o jogo
        void clean();
        SDL_Renderer* getRenderer(){ return g_Renderer; }
    private:
         //Construtor e destrutor da class
        Game();
        ~Game();
        static Game* s_pInstance;

        bool isRunning;
        SDL_Window* g_Window;
        SDL_Renderer* g_Renderer;
        int m_currentFrame;

        GameObject* m_go;
        GameObject* m_player;
        GameObject* m_enemy;

        std::vector<GameObject*> m_GameObjects;
};

typedef Game TheGame;

#endif