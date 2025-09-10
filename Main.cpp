//#define SDL_MAIN_HANDLED
#include <string>
#include  <stdio.h>
#include <SDL.h>
// criando constantes da largura e altura da janela
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT = 580;
//enum para constants de input teclado
enum KeyPressSurface{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//função de iniciar a janela
bool init();
//função de carregar imagem na surface da tela
bool loadMedia();
// função para limpar a surface, anular ponteiros e fechar sdl2
void close();

//funçao que carrega loads individual da image
SDL_Surface* loadSurface(std::string path);
//instancia da janela
SDL_Window* gWindow = NULL;
//instancia da surface da tila PRINCIPAL
SDL_Surface* gscreenSurface = NULL;
//array de surgace  com o numero maximo do enum
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
//Currend displayed image
SDL_Surface* gCurrentSurface = NULL;

//iniciar  o  SDL2, janela e a surfaceprincipaç
bool init(){
   
    bool sucess = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        printf("Problemas para iniciar o SDL SDL_ERROR:%s\n",SDL_GetError());
        sucess = false;
    }else{
        gWindow = SDL_CreateWindow("Argonauts",SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        
        if(gWindow == NULL){
            printf("Problemas para iniciar janela !! SDL_ERROR:%s\n",SDL_GetError());
                    sucess = false;

        }else{
                    
            gscreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
        return sucess;

    }

SDL_Surface* loadSurface(std::string path){
    //carregando  uma imagem carregada pelo caminho
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL){
        printf("Erro ao carregar imagem %s ! SDL Error: %s\n",path.c_str(), SDL_GetError);
    }
    return loadedSurface;
}

bool loadMedia(){
    bool sucess = true;

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./assets/press.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
        printf("Falha ao tentar carregar a  imagem padrão");
        sucess = false;
    }

    
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./assets/up.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL){
         printf("Falha ao tentar carregar a  imagem cima");
         sucess=false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./assets/down.bmp");
        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL){
            printf("Falha ao tentar carregar a  imagem Baixo");
            sucess=false;
        }

   gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./assets/left.bmp");
        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
            printf("Falha ao tentar carregar a  imagem Esquerda");
            sucess=false;
        }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./assets/right.bmp");
        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL){
            printf("Falha ao tentar carregar a  imagem direita");
            sucess=false;
        }

 return sucess;
}



void close(){
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
    SDL_FreeSurface(gKeyPressSurfaces[i]);
    gKeyPressSurfaces[i] = nullptr;
    }
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    

    SDL_Quit();
} 

int main(int argc, char* argv[]){

    if(!init()){

       printf("Problema para iniciar a janela");
    }else{
        if(!loadMedia()){
            printf("Problema para iniciar a janela");

        }else{
            bool quit = false;
            SDL_Event e;

            gCurrentSurface =gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            while(!quit){
                //tratamento da lista de eventos
                while(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT){
                        // se de clicar no x sai do programa
                        quit = true;
                        //se um tecla for precionada
                    }else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];break;
                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];break;
                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];break;
                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];break;
                                default:
                                gCurrentSurface= gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]; break;

                        }

                    }
                }
                // aplicando a a imagem criada no surfacede imagem para a surface principal
                SDL_BlitSurface(gCurrentSurface,nullptr,gscreenSurface,NULL);
                //atualizando a janela
                SDL_UpdateWindowSurface(gWindow);
            }

        }
    }
    close();

    return 0;
 }








