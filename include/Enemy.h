#ifndef _Enemy_
#define _Enemy_
#include "SDLGameObject.h"

class Enemy : public SDLGameObject{
     public:
        Enemy(const LoaderParams* pParams);
        void draw();
        void update();
        void clean();   
};
#endif