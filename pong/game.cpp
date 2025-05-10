#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "game.h"

Game::Game(const int screenWidth, const int screenHeight, const std::string &title) {
    this->screenHeight  = screenHeight;
    this->screenWidth = screenWidth;
    this->title = title;
    isRunning = true;
    hasInit = false;
    scores = {0, 0};
}

Game::~Game() {
    close();
}

bool Game::init() {
    if (hasInit) {
        std::cout << "Game has already been initialized" << std::endl;
        return false;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Failed to initialize video " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() != 0) {
        std::cout << "Failed to initialize font " << TTF_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Failed to create window " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        std::cout << "Failed to create renderer " << SDL_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont("pong/font.ttf", 30);
    if (font == NULL) {
        std::cout << "Failed to open font " << TTF_GetError() << std::endl;
        return false;
    }

    hasInit = true;
    return true;
}

bool Game::running() {
    return isRunning;
}

void Game::event(const SDL_Event &e) {
    if (e.type == SDL_QUIT) {
        isRunning = false;
    }
}

void Game::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderDrawLine(renderer, screenWidth / 2, 0, screenWidth / 2, screenHeight);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect midSquare = {screenWidth / 2 - 10, screenHeight / 2 - 10, 20, 20};
    SDL_RenderFillRect(renderer, &midSquare);
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderDrawRect(renderer, &midSquare);
}

void Game::render() {
    std::stringstream stringScore;
    stringScore << scores.p1;
    loadText(stringScore.str(), 1);
    stringScore.str("");
    stringScore << scores.p2;
    loadText(stringScore.str(), 2);
    SDL_RenderPresent(renderer);
}

void Game::close() {
    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }

    SDL_Quit();
    TTF_Quit();
}

void Game::loadText(const std::string &score, const int player) {
    SDL_Color textColor = {100, 100, 100, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, score.c_str(), textColor);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect position = {0, 20, surface->w, surface->h};
    if (player == 1) {
        position.x = screenWidth / 2 - 30 - position.w;
    }
    else {
        position.x = screenWidth / 2 + 30;
    }

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &position);
    SDL_DestroyTexture(texture);
}

void Game::updateScore(int player) {
    if (player == 1) {
        scores.p1++;
    }
    else if (player == 2){
        scores.p2++;
    }
}