#ifndef _GameObject_
#define _GameObject_

#include "LoaderParams.h"


// é uma forward declaration (declaração antecipada). para nao precisar dar o include aqui
//Basicamente você está dizendo ao compilador: “Ei, existe um tipo chamado SDL_Renderer em algum lugar. Não sei ainda os detalhes, mas existe.”
struct SDL_Renderer;

class GameObject{

    public:
        virtual void load() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean() = 0;

    protected:
       GameObject(const LoaderParams* pParams){}
};

#endif