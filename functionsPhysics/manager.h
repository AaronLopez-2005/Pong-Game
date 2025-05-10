#ifndef MANAGER_H
#define MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Manager{
    public:
        Manager();
        bool init(const std::string windowTitle, const int screen_height, const int screen_width, const std::string path = "", const int pixelSize = 0);
        bool isRunning();
        void clearRender();
        void drawToScreen();
        void handleEvents(SDL_Event &e);
        void close();
        int getWindowHeight() const {return screen_h;}
        int getWindowWidth() const {return screen_w;}
        ~Manager();
        SDL_Window *window;
        SDL_Renderer *renderer;
        TTF_Font *font;

    private:
        int screen_h;
        int screen_w;
        bool hasInit;
        bool running;
};

#endif