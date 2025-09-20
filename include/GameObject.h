#ifndef _GameObject_
#define _GameObject_

#include <string>

// é uma forward declaration (declaração antecipada). para nao precisar dar o include aqui
//Basicamente você está dizendo ao compilador: “Ei, existe um tipo chamado SDL_Renderer em algum lugar. Não sei ainda os detalhes, mas existe.”
struct SDL_Renderer;

class GameObject{

    public:
        void load(int x , int y , int width, int height, std::string textureID);
        void draw(SDL_Renderer* pRenderer);
        void update();
        void clean();

    protected:
        std::string m_textureID;
        
        int m_currentFrame;
        int m_currentRow;

        int m_x;
        int m_y;
        
        int m_width;
        int m_height;
};

#endif