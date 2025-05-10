#include <SDL.h>
#include "dot.h"
#include "vector2D.h"

Dot::Dot(int screen_w, int screen_h) {
    height = 10;
    width = 10;
    position.x = (screen_w - width) / 2;
    position.y = (screen_h - height) / 2;
    gravity.x = 0;
    friction.y = 0;
    friction.x = 0.01;
    gravity.y = 2;
    screen_height = screen_h;
    screen_width = screen_w;
    onGround = false; 
}

Dot::Dot(int screen_w, int screen_h, int x, int y)
{
    velocity.y = -35;
    velocity.x = 4;
    height = 10;
    width = 10;
    position.x = x;
    position.y = y;
    gravity.x = 0;
    friction.y = 0;
    friction.x = 0.01;
    gravity.y = 2;
    screen_height = screen_h;
    screen_width = screen_w;
    onGround = false;
}

void Dot::move()
{
    onGround = false;
    velocity = velocity + gravity * Vector2D::dt;
    position = position + velocity * Vector2D::dt;
    if (position.y + height > screen_height)
    {
        onGround = true;
        position.y = screen_height - height;
        velocity.y *= -0.85;
        if (velocity.x > 0 && !moving) {
            velocity.x = velocity.x - friction.x * Vector2D::dt;
        }
        else if (velocity.x < 0 && !moving){
            velocity.x = velocity.x + friction.x * Vector2D::dt;
        }
    }
    else if (position.y < 0)
    {
        position.y = 0;
        velocity.y *= -1;
    }

    if (position.x + width > screen_width || position.x < 0)
    {
        position.x = position.x - velocity.x;
        velocity.x *= -0.5;
    }
}

void Dot::draw(SDL_Renderer *&renderer)
{
    SDL_Rect drawRect = {(int)position.x, (int)position.y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &drawRect);
}

void Dot::handleEvents(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        moving = true;
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
                if (onGround) {
                    velocity.y += -30;
                }
                break;
            case SDLK_a:
                velocity.x = -10;
                break;
            case SDLK_d:
                velocity.x = 10;
                break;
            default:
                moving = false;
                break;
            
        }
    }
    else if (e.type == SDL_KEYUP) {
        moving = false;
    }
}

void Dot::graph(SDL_Renderer *&renderer) {
    bool inside = true;
    while(inside) {
        velocity = velocity + gravity * Vector2D::dt;
        position = position + velocity * Vector2D::dt;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, position.x, position.y);
        if (position.x < 0 || position.x > screen_width) {
            inside = false;
            position.x = 0;
            position.y = screen_height;
            velocity.x = 4;
            velocity.y = -35;
        }

        std::cout << position.x << " " << position.y << " " << gravity.y << std::endl;
    }
}
