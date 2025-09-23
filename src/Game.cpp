#include "Game.h"
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


Game* Game::s_pInstance = 0;


Game::Game(){

}

Game* Game::Instance(){
    if(s_pInstance == 0 ){
        s_pInstance = new Game();
        return s_pInstance;
    }
    return s_pInstance;
}

/*
    FLAGS QUE PODEM IR JUNTAS OU OPCIONAL NO CREATEwINDWO
SDL_WINDOW_FULLSCREEN: Deixa a janela em modo de tela cheia.
SDL_WINDOW_OPENGL: Indica que a janela será usada como um contexto OpenGL. É necessário para renderização com essa API.
SDL_WINDOW_SHOWN: A janela é criada visível. Essa é a flag padrão na maioria dos casos.
SDL_WINDOW_HIDDEN: A janela é criada escondida. Você pode mostrá-la depois.
SDL_WINDOW_BORDERLESS: A janela não terá bordas ou botões de controle (como fechar, minimizar, maximizar).
SDL_WINDOW_RESIZABLE: Permite que o usuário redimensione a janela.
SDL_WINDOW_MINIMIZED: A janela começa minimizada.
SDL_WINDOW_MAXIMIZED: A janela começa maximizada.
SDL_WINDOW_INPUT_GRABBED: A janela "agarra" o foco do mouse e do teclado, forçando-os a permanecer dentro da janela.
SDL_WINDOW_INPUT_FOCUS: Indica que a janela tem o foco do teclado (está ativa para receber entradas do teclado).
SDL_WINDOW_MOUSE_FOCUS: Indica que a janela tem o foco do mouse (o cursor do mouse está sobre ela).
SDL_WINDOW_FOREIGN: Indica que a janela foi criada por uma API externa, e não pelo SDL.

*/


bool Game::init(const char* title, int xpos, int ypos, int widthSize,int heightSize, bool fullscreen){
    bool sucess = true;

    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    //iniciando o SDL, a janela e o render
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
        printf("Erro ao tentar inciar o SDL ! %s\n",SDL_GetError());
         sucess = false;
    }else{
        // criando a janela
        g_Window = SDL_CreateWindow(title, xpos,ypos, widthSize,heightSize, flags);
        if(g_Window == NULL){
            printf("Erro ao abrir a janela ! %s\n",SDL_GetError());
            sucess = false;
        }else{
            // iniciando o render
            g_Renderer = SDL_CreateRenderer(g_Window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(g_Renderer == NULL){
                printf("Erro ao iniciar o render! %s\n",SDL_GetError());
                sucess = false;
            }else{

                //definindo a cor para limpar o render,nesse caso preto
                SDL_SetRenderDrawColor(g_Renderer,255,0,0,255);
                //iniciando o SDL_IMAGE para carregar outros tipos de imagem. + moderno
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if(!(IMG_Init(imgFlags) & imgFlags) ){
                    printf( "Problema ao iniciar SDL_IMG ! %s\n", IMG_GetError());
                    sucess = false;
                }
                        
                if(!TheTextureManager::Instance()->load("assets/animate-alpha.png","animate",g_Renderer)){
                    sucess = false;
                }

                m_GameObjects.push_back(new Player(new LoaderParams(150,150,128,82,"animate")));
                m_GameObjects.push_back(new Enemy(new LoaderParams(200,200,128,82,"animate")));
                

            }
        }
    }
    // INICIANDO O JOGO E O MAIN LOOP   
    isRunning = true;
    return sucess;
}


void Game::handleEvents(){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                isRunning = false; break;
            default:  break;
        }
    }

}

void Game::update(){
    for(std::vector<GameObject*>::size_type i = 0; i< m_GameObjects.size() ; i++){
        m_GameObjects[i]->update();
    }
}

void Game::render(){
    // limpando o render  para desenhar
    SDL_RenderClear(g_Renderer);
  
    for(std::vector<GameObject*>::size_type i = 0; i < m_GameObjects.size();i++){
        m_GameObjects[i]->draw();
    }
   // Renderizando a tela
    SDL_RenderPresent(g_Renderer);
}


void Game::clean(){
   
    // Destruindo a tela
    SDL_DestroyWindow(g_Window);
    g_Window =  nullptr;
    // Destruindo o render
    SDL_DestroyRenderer(g_Renderer);
    g_Renderer = nullptr;
    IMG_Quit(); // fechando o SDL_IMAGE
    SDL_Quit(); // fechando o SDL
}


Game::~Game(){
    clean();
}