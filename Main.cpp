#define SDL_MAIN_HANDLED
#include  <stdio.h>
#include <SDL.h>
// criando constantes da largura e altura da janela
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT = 580;

SDL_Window* gWindow = NULL;
SDL_Surface* gSreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init();
bool loadMedia();
void close();


bool init(){
   
    bool sucess = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Problemas para iniciar o SDL SDL_ERROR:%s\n",SDL_GetError());
        sucess = false;
    }else{
        gWindow = SDL_CreateWindow("Argonauts",SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        
        if(gWindow == NULL){
            printf("Problemas para iniciar janela !! SDL_ERROR:%s\n",SDL_GetError());
                    sucess = false;

        }else{
                    
            gSreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
        return sucess;

    }

bool loadMedia(){
    bool sucess = true;

    //carrear imagem inicial
    gHelloWorld = SDL_LoadBMP("./assets/hello_world.bmp");
    if(gHelloWorld == NULL){
        printf("Problemas para carregar a imagem !! SDL_ERROR:%s\n",SDL_GetError());
        sucess= false;
    }
   
    return sucess;
}

void close(){
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
} 

int main(int argc, char* argv[]){

    if(!init()){
        printf("Fala ao inicializar!\n");
    }else{
        if(!loadMedia()){
            printf( "Falha ao carregar mídia!\n" );

        }else{
            SDL_BlitSurface( gHelloWorld, NULL, gSreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);

            SDL_Event e;
            bool quit = false;

            while(quit == false){
                while( SDL_PollEvent( &e )) {
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                }
            }

        }
    }
    
    close();

    return 0;
 }








