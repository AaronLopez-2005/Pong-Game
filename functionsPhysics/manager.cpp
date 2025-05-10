#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "manager.h"

Manager::Manager()  {
    window = NULL;
    renderer = NULL;
    font = NULL;
    hasInit = false;
    running = true;
}

bool Manager::init(const std::string windowTitle, const int screen_height, const int screen_width, const std::string path, const int pixelSize) {
    // Cannot initialize systems twice
    if (hasInit) {
        std::cout << "Systems have already been initialized" << std::endl;
        return false;
    }

    // Initialize video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL could not initialize systems " << SDL_GetError() << std::endl;
        return false;
    }

    // Initializes Image
    if (IMG_Init(IMG_INIT_PNG)  != IMG_INIT_PNG) {
        std::cout << "IMG was not able to initailze " << IMG_GetError() << std::endl;
        return false;
    }

    // Initializes True Type Font
    if (TTF_Init() != 0) {
        std::cout << "TTF was not able to initialize " << TTF_GetError() << std::endl;
        return false;
    }

    // Creates window and checks for error
    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "SDL was not able to create window " << SDL_GetError() << std::endl;
        return false;
    }

    // Creates window and checks for error
    renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        std::cout << "SDL was not able to create renderer " << SDL_GetError() << std::endl;
        return false;
    }

    // Opens font if there is a path
    if (path != "") {
        font = TTF_OpenFont(path.c_str(), pixelSize);
        if (font == NULL) {
            std::cout << "TTF font was not able to open font " << path << " " << TTF_GetError() << std::endl;
            return false;
        }
    }

    screen_h = screen_height;
    screen_w = screen_width;

    hasInit = true;
    return true;
}

bool Manager::isRunning() {
    return running;
}

void Manager::handleEvents(SDL_Event &e) {
    if (e.type == SDL_QUIT) {
        running = false;
    }
}

void Manager::clearRender() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Manager::drawToScreen() {
    SDL_RenderPresent(renderer);
}


void Manager::close() {
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
}

Manager::~Manager() {
    close();
}