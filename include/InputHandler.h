#ifndef _InputHandler_
#define _InputHandler_
#include <SDL.h>
#include <vector>

class InputHandler{
    public:
        static InputHandler* Instance();
        void initialiseJoysticks();
        bool joysticksInitialised();
        void update();
        void clean();

    private:
        InputHandler();
        ~InputHandler();

    std::vector<SDL_Joystick*> m_joysticks;  
    bool m_bJoysticksInitialised;
    static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;

#endif