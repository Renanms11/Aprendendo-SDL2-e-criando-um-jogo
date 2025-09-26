#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include <SDL.h>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams){
    
}


void Player::draw(){
   SDLGameObject::draw();
}

void Player::update(){
  m_currentFrame = int(((SDL_GetTicks() / 100) % 6 ));
  m_acceleration.setX(1);
  SDLGameObject::update();
}

void Player::clean(){
    
}