#define SDL_MAIN_HANDLED
#include  <stdio.h>
#include <SDL.h>
// criando constantes da largura e altura da janela
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT = 580;

int main(int argc, char* argv[]){
    //criando os ponteiros da janela
    SDL_Window* window = NULL;
    //declarando a variavel da superficie
    SDL_Surface* screenSurface = NULL;

    //iniciando o sdl, so com video e fazendo um if para garantir o funcionamento
    if(SDL_Init(SDL_INIT_VIDEO) <0){
       printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }else{
        // instanciando a janela, nome,posição x, posição y, largura,altura , modo mostrar
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    // veriaficando se a janela foi criada para pintar na surpeficie
        if(window == NULL){
            printf("window could not be create! SDL_Error: %s\n",SDL_GetError());
        }else{
            //instanciando a surpeficie da janela
            screenSurface = SDL_GetWindowSurface(window);

            //pintando a superficie de branco
            SDL_FillRect(screenSurface,NULL, SDL_MapRGB(screenSurface ->format,255,255,0));
            //atualizando a superficie.
            SDL_UpdateWindowSurface(window);
           SDL_Event e;
            bool quit = false; 
            while( quit == false ){ 
                while( SDL_PollEvent( &e ) ){ 
                    if( e.type == SDL_QUIT ) quit = true; 
                    } 
                }
        }
        //destruindo a janela
        SDL_DestroyWindow(window);
        //fechando o subsistema do sdl
        SDL_Quit();

        return 0;
    }








}