#ifndef DOT_H
#define DOT_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "vector2D.h"

class Dot {
    public:
        Dot(int screen_w, int screen_h);
        Dot (int screen_w, int screen_h, int x, int y);
        void move();
        void draw(SDL_Renderer *&renderer);
        void graph(SDL_Renderer *&renderer);
        void handleEvents(SDL_Event &e);
    private:
        Vector2D velocity;
        Vector2D position;
        Vector2D gravity;
        Vector2D friction;
        int height;
        int width;
        int screen_height;
        int screen_width;
        bool onGround;
        bool moving;
        std::vector<SDL_Rect> points;

};

#endif