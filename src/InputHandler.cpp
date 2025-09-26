#include "InputHandler.h"
#include <SDL.h>
#include<stdio.h>

InputHandler* InputHandler::s_pInstance = nullptr;

    InputHandler* InputHandler::Instance(){
    if(s_pInstance  == 0){
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
}

void InputHandler::initialiseJoysticks(){
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    int numJoysticks = SDL_NumJoysticks();
    if(SDL_NumJoysticks() > 0){
        for(int i = 0; i < SDL_NumJoysticks();i++){ 
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            
            if(SDL_JoystickGetAttached(joy) == 1){
                m_joysticks.push_back(joy);
            }else{
                printf("Erro ao inicializar os joystick",SDL_GetError());
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        printf("Joysticks inicializado nº:%s\n", m_joysticks.size());
    }else{
        m_bJoysticksInitialised = false;
    }

}

bool InputHandler::joysticksInitialised(){
    return InputHandler::m_bJoysticksInitialised;
}
void InputHandler::update(){

}
void InputHandler::clean(){
    
}