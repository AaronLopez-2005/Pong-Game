#ifndef BALL_H
#define BALL_H

#include <SDL.h>

struct Velocity {
    int x;
    int y;
};

struct scDim
{
    int screenWidth;
    int screenHeight;
};

class Ball {
    public:
        Ball(const int screenWidth, const int screenHeight);
        void reset();
        void move();
        void draw(SDL_Renderer *&renderer);
        bool checkCollision(SDL_Rect obj);
        int checkOutside();
    private:
        SDL_Rect dimension;
        Velocity vel;
        scDim sDim;
        bool collided;
};

#endif