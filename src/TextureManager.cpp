#include "textureManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <map>

TextureManager* TextureManager::s_pInstance = 0;


TextureManager::TextureManager(){

}

TextureManager::~TextureManager(){

}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer){
    bool sucess = true;
    SDL_Surface*  pTempSurface  = IMG_Load(fileName.c_str());
    if(pTempSurface == nullptr){
        printf("Erro ao preparar a textura na surface do arquivo %s! %s\n",fileName.c_str(),SDL_GetError());
            sucess = false;
    }else{
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pTempSurface);
        if(pTexture == nullptr){
            printf("Erro ao tentar transformar a surface em textura! SDL Error %s\n",SDL_GetError());
            sucess = false;
        }else{
            SDL_FreeSurface(pTempSurface);
            m_TextureMap[id] = pTexture;
        }
    }
    return sucess;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip){
    // Retangulos e origem e destino
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;

    destRect.w = srcRect.w = width;
    destRect.h = srcRect.h = height;
    destRect.x = x;
    destRect.y = y;

    // SDL_RenderCopy(g_Renderer, gTexture, 0,0); os os 2 ultimos parametros forem null ele renderiza a figura toda no render todo
    //pega o render, a textura, a parte da texture e aonde renderiza
    // SDL_RenderCopy(g_Renderer, gTexture, &g_sourceRectangle, &g_destinationRectangle);
   // versão extendidad  do rendercopy, permitindo rotação e inversaõ

    SDL_RenderCopyEx(pRenderer,m_TextureMap[id], &srcRect, &destRect,0,0,flip);
}


void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,int currentRow,int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip){
    // Retangulos e origem e destino
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow -1);
    destRect.w = srcRect.w = width;
    destRect.h = srcRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer,m_TextureMap[id], &srcRect, &destRect,0,0,flip);
}


TextureManager* TextureManager::Instance(){
    if(s_pInstance == 0){
        s_pInstance = new TextureManager();
        return s_pInstance;
    }
    return s_pInstance;

}