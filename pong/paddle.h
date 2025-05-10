#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include <iostream>

struct screenDim {
    int screenWidth;
    int screenHeight;
};

class Paddle {
    public:
        static int objId;

        Paddle(const int screenWidth, const int screenHeight);
        void Draw(SDL_Renderer *&renderer) const;
        void HandleEvent(const SDL_Event &e);
        void Move();
        SDL_Rect getDimension() const {return dimension;}
        
    private:
        screenDim sDim;
        int vel;
        SDL_Rect dimension;
        SDL_Color color;
        int id;
};

#endif