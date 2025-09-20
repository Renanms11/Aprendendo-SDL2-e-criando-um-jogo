#ifndef _Player_
#define _Player_

#include "GameObject.h"

class Player : public GameObject {
    public:
        void load(int x , int y , int width, int height, std::string textureID);      
        void draw(SDL_Renderer* pRenderer);
        void update();
        void clean();
    
        
};




#endif