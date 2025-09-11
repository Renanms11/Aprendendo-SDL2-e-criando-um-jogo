#include <string>
#include <stdio.h>
#include <SDL.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
SDL_Surface* loadSurface(std::string path);
void close();

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gStretchedSurface = NULL;

bool init(){
    bool sucess = true;
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
        printf("Erro ao iniciar o SDL!! SDL Erro: %s\n",SDL_GetError());
        sucess = false;
    }else{
        gWindow = SDL_CreateWindow("Melhorando carregamento de imagem",SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == nullptr){
            printf("Erro ao abrir a janela!! SDL Erro: %s\n",SDL_GetError());
            sucess = false;
        }else{
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }

    }
    return sucess;
}

bool loadMedia(){
    bool sucess = true;
    gStretchedSurface = loadSurface("./assets/stretch.bmp");
    if(gStretchedSurface == nullptr){
       printf("Problema a carregar a imagem na surface!");
       sucess = false;
    }
    return sucess ;
}

SDL_Surface* loadSurface(std::string path){
   
    // imagem final otimizada
    SDL_Surface* optimizedSurface = nullptr;

    //carregando a imagem especifica
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == nullptr){
        printf("Problema ao carregar a imagem !! SDL Error: %s\n",SDL_GetError());
    }else{
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface ->format,0);
        if(optimizedSurface == nullptr){
            printf("Não foi possivel otimizar a imagem %s! SDL Error: %s\n",
                path.c_str(),SDL_GetError());

        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;

}


void close(){
    SDL_FreeSurface( gStretchedSurface );
	gStretchedSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();

}


int main(int argc,char* argv[]){

    if(!init()){
        printf("Problema de iniciar o programa");
    }else{
        if(!loadMedia()){
            printf("Problema de iniciar o programa");
        }else{
            bool quit = false;
            SDL_Event e;
            while(!quit){
                while(SDL_PollEvent(&e) !=0){
                    if(e.type == SDL_QUIT ){ 
                        quit = true;
                        }
                        
                    }
                    // esticando  a imagme
                        SDL_Rect stretchRect;
                        stretchRect.x =0;
                        stretchRect.y=0;
                        stretchRect.w = SCREEN_WIDTH;
                        stretchRect.h= SCREEN_HEIGHT;
                        SDL_BlitScaled(gStretchedSurface,nullptr,gScreenSurface,&stretchRect);
                        SDL_UpdateWindowSurface(gWindow);

                }
            }

        }

    
    close();
    return 0;
}






