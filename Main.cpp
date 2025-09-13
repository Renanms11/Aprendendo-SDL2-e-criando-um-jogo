#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gwindow = nullptr;
// O Renderer usa aceleração via hardware da gpu, enquato  a surface usa a cpu
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = nullptr;


bool init ();
SDL_Texture* loadTexture(std::string path);
bool loadMedia();
void close();


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
            // iniciando o sdl hint/dicas para 
            /* 
                SDL_SetHint(hint, value) É uma função da SDL usada para configurar dicas (hints) 
                de como a biblioteca deve se comportar em certas situações.Retorna SDL_TRUE (1) se conseguiu 
                aplicar a configuração, ou SDL_FALSE (0) se não conseguiu.
                "0" → Nearest pixel sampling (sem filtro). A textura fica "pixelada" quando ampliada.
                "1" → Linear filtering. Faz uma interpolação entre pixels, 
                deixando a imagem mais suave, mas pode borrar.
                "2" → Anisotropic filtering (se suportado). Deixa ainda mais nítido 
                quando a textura é inclinada/esticada. 
            */

            if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
                printf("Alerta filtro de textura linear não abilitada !");
            }
            // iniciando o renderer, com a janela, -1 para ser qualuqer api, e flag para ser acelerado por hardware
            gRenderer = SDL_CreateRenderer(gwindow,-1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == nullptr){
                printf("O Renderer não foi criada SDL Error:%s\n",SDL_GetError());
                sucess = false;
            }else{
                SDL_SetRenderDrawColor(gRenderer,50,50,255,255);
                //pegando uma flag para iniciar o png
                int imgFlags = IMG_INIT_PNG;
                //iniciando o SDL_Image
                if(!IMG_Init(imgFlags) & imgFlags){
                    printf("Erro ao inicializar SDL IMAGE! SDL Error: %s\n",IMG_GetError());
                    sucess = false;
                }

            }

        }
    }
    return sucess;
}


SDL_Texture* loadTexture(std::string path){
    // surface para  otimizar a imagem
    SDL_Texture* newTexture = nullptr;
    // surface para carregar a imagem png
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        printf("Não foi possivel carregar a imagem %s! SDL_image Error: %s\n",
            path.c_str() ,IMG_GetError());
    }else{
        //criando uma textura apartir de uma surface,recebe o render e a surface
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture ==NULL){
            printf("Não foi criar a textura do %s! SDL_image Error: %s\n",
            path.c_str() ,SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
        }
        return newTexture;
}



bool loadMedia(){
    bool sucess = true;
    gTexture = loadTexture("./assets/viewport.png");
    //não tem nada para carregar
    return sucess;
}

void close(){
    // Destruindo a textura
    
    // destruindo o render
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gwindow);
    gwindow = NULL;
    // fecahdno o subsistema de image
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

                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                SDL_RenderClear(gRenderer); //limpa a tela com a cor passada

                //viewport, e como renderizar a mesma imagem varias vezes na mesma janela, ->
                //util para fazer o mini map

                // lado esquerdo do alto viewport
                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH/2 ;
                topLeftViewport.h = SCREEN_HEIGHT/2;
                SDL_RenderSetViewport(gRenderer,&topLeftViewport);
                //renderizando a textura na tela
                SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);


                // lado direito do alto viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH/2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH/2;
                topRightViewport.h = SCREEN_HEIGHT/2;
                SDL_RenderSetViewport(gRenderer,&topRightViewport);
                SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);


                //viewport completa de baixo
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y =SCREEN_HEIGHT/2 ;
                bottomViewport.w =SCREEN_WIDTH ;
                bottomViewport.h =SCREEN_HEIGHT/2 ;
                SDL_RenderSetViewport(gRenderer , &bottomViewport);
                SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);

                // renderiza
                SDL_RenderPresent( gRenderer );

            }
            
        }

    }
    close();
    return 0;
}






