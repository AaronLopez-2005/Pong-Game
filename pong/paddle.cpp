#include <SDL.h>
#include <iostream>
#include "paddle.h"

int Paddle::objId = 0;

Paddle::Paddle(const int screenWidth, const int screenHeight) {
    id = objId;
    objId++;

    sDim = {screenWidth, screenHeight};

    dimension.h = 100;
    dimension.w = 15;
    dimension.y = (sDim.screenHeight - dimension.h) / 2;
    if (id == 0) {
        dimension.x = 30;
    }
    else {
        dimension.x = sDim.screenWidth - 30 - dimension.w;
    }

    vel = 0;

    color = {255, 255, 255, 255};

    std::cout << id << std::endl;
}

void Paddle::HandleEvent(const SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (id == 0) {
            switch(e.key.keysym.sym) {
                case SDLK_w:
                    vel -= 10;
                    break;
                case SDLK_s:
                    vel += 10;
                    break;
            }
        }

        else {
            switch(e.key.keysym.sym) {
                case SDLK_UP:
                    vel -= 10;
                    break;
                case SDLK_DOWN:
                    vel += 10;
                    break;
            }
        }
    }

    else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        if (id == 0) {
            switch(e.key.keysym.sym) {
                case SDLK_w:
                    vel += 10;
                    break;
                case SDLK_s:
                    vel -= 10;
                    break;
            }
        }

        else {
            switch(e.key.keysym.sym) {
                case SDLK_UP:
                    vel += 10;
                    break;
                case SDLK_DOWN:
                    vel -= 10;
                    break;
            }
        }
    }
}

void Paddle::Draw(SDL_Renderer *&renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &dimension);
}

void Paddle::Move(){
    dimension.y += vel;

    if (dimension.y < 0 || dimension.y + dimension.h > sDim.screenHeight) {
        dimension.y -= vel;
    }
}