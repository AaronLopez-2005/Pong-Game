#include <SDL.h>
#include <iostream>
#include "ball.h"
#include <random>

Ball::Ball(const int screenWidth, const int screenHeight) {
    sDim.screenHeight = screenHeight;
    sDim.screenWidth = screenWidth;

    vel = {5, 5};
    dimension.h = 10;
    dimension.w = 10;
    dimension.x = (sDim.screenWidth - dimension.w) / 2;
    dimension.y = (sDim.screenHeight - dimension.h) / 2;
}

void Ball::reset() {
    vel = {-vel.x, -vel.y};

    dimension.x = (sDim.screenWidth - dimension.w) / 2;
    dimension.y = (sDim.screenHeight - dimension.h) / 2;
}

void Ball::move() {
    dimension.x += vel.x;
    dimension.y += vel.y;

    if (collided) {
        vel.x *= -1;
        dimension.x += vel.x; 
    }
    if (dimension.y < 0 || dimension.y + dimension.h > sDim.screenHeight) {
        vel.y *= -1;
        dimension.y += vel.y;
    }
}

void Ball::draw(SDL_Renderer *&renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &dimension);
}

bool Ball::checkCollision(SDL_Rect obj) {
    
    if (dimension.x + vel.x > obj.x && dimension.x + vel.x < obj.x + obj.w || dimension.x + dimension.w + vel.x > obj.x && dimension.x + dimension.w + vel.x < obj.x + obj.w) {
        if (dimension.y + vel.y > obj.y && dimension.y + vel.y < obj.y + obj.h || dimension.y + dimension.h + vel.y > obj.y && dimension.y + dimension.h + vel.y < obj.y + obj.h) {
            collided = true;
            return true;
        }
    }

    collided = false;
    return false;
}

int Ball::checkOutside() {
    if (dimension.x < 0) {
        reset();
        return 2;
    }
    else if(dimension.x + dimension.w > sDim.screenWidth) {
        reset();
        return 1;
    }
    else {
        return 0;
    }
}