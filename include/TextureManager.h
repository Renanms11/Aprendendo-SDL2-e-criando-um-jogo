// CLASSE GERENCIADORA DE TEXTURAS
#ifndef _Texture_
#define _Texture_

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>// usar o collection map

class TextureManager{
    public:
       
        ~TextureManager();
        //função para carregar texturas, recebe o do arquivo com as imagens, o id que nos referimos a textura e o render
        bool load(std::string fileName , std::string id , SDL_Renderer*  pRenderer);
        //função para desenha, o id, pos x e y, largura e altura da imagem, o render, e por padrao sem rotaçao
        void draw(std::string id, int x, int y, int width, int height, SDL_Renderer*  pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        //funçaõ para desenhar animação. o mesmo de cima com o numero da linha do spritesheep, e o atual frame
        void drawFrame(std::string id,int x, int y, int width, int height,int currentRow, int currentFrame, SDL_Renderer*  pRenderer, SDL_RendererFlip = SDL_FLIP_NONE);
        // criando o instanciador unico da classe.(com logica para haver so um objeto por jogo)
        static TextureManager* Instance(); // o static e para falar que o que o metodo e de class e não de uma instancia.
    private:
        TextureManager();//transformando a class em singleton( que so pode ter 1 instancia para todo programa)
        // variavel para controlar a instanciação da classe
        static TextureManager* s_pInstance;
        // Mapa que guarda todas as texturas, chave-String : valor-SDL_Texture
        std::map<std::string, SDL_Texture*> m_TextureMap;
};

/*
            DEFININDO UMA APELIDIO PARA CLASSE   
    TextureManager* tm1 = TextureManager::Instance();  // jeito normal
    TheTextureManager* tm2 = TheTextureManager::Instance();  // usando o typedef
*/
typedef TextureManager TheTextureManager;

#endif 