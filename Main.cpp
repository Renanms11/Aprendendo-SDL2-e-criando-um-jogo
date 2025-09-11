#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gwindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gImageSurface = nullptr;

bool init ();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

bool init(){
    bool sucess = true;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        printf("Erro ao iniciar o SDL ! SDL Error: %s\n",SDL_GetError());
        sucess = false;
    }else{
        gwindow = SDL_CreateWindow("Argonaut",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(gwindow == nullptr){
            printf("Erro ao abrir a janela ! SDL Error: %s\n",SDL_GetError());
            sucess = false;
        }else{
            //inicializar o carregador png
            int imgFlags = IMG_INIT_PNG;
            if(!IMG_Init(imgFlags) & imgFlags){
                printf("Erro ao inicializar SDL IMAGE! SDL Error: %s\n",IMG_GetError());
                sucess = false;
            }else{
                 gScreenSurface = SDL_GetWindowSurface( gwindow );
            }
        }
    }
    return sucess;
}


SDL_Surface* loadSurface(std::string path){
    // surface para  otimizar a imagem
    SDL_Surface* optimizedSurface = nullptr;
    // surface para carregar a imagem png
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        printf("Não foi possivel carregar a imagem %s! SDL_image Error: %s\n",
            path.c_str() ,IMG_GetError());
    }else{
        //convertendo a imagem no formato da tela
        optimizedSurface = SDL_ConvertSurface(loadedSurface,gScreenSurface-> format,0 );
        if(optimizedSurface ==NULL){
            printf("Não foi possivel otimizar a imagem %s! SDL_image Error: %s\n",
            path.c_str() ,IMG_GetError());
        }
        SDL_FreeSurface(loadedSurface);
        }
        return optimizedSurface;
}



bool loadMedia(){
    bool sucess = true;
    gImageSurface = loadSurface("./assets/loaded.png");
    if(gImageSurface == nullptr){
        printf( "Falha ao carregar a imagem!\n" );
        sucess=false;
    }
    return sucess;
}

void close(){
    SDL_FreeSurface(gImageSurface);
    gImageSurface = nullptr;

    SDL_DestroyWindow(gwindow);
    IMG_Quit();
    SDL_Quit();
}



int main(int argc , char* argv[]){

    if(!init()){
        printf("Problema ao iniciar o jogo!");
    }else{
        if(!loadMedia()){
            printf("Problema ao iniciar o jogo!");
        }else{
            bool quit = false;
            SDL_Event e;
            while (quit == false){
              while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT) quit = true;
                }
            SDL_BlitSurface( gImageSurface, NULL, gScreenSurface, NULL );
            //Update the surface
            SDL_UpdateWindowSurface( gwindow);

            }
            
        }

    }
    close();
    return 0;
}






