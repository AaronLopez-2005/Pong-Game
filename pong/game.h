#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

struct Scores {
    int p1;
    int p2;
};

class Game {
    public:
        SDL_Renderer *renderer;
        SDL_Window *window;
        Game(const int screenWidth, const int screenHeight, const std::string &title);
        ~Game();
        bool init();
        bool running();
        void event(const SDL_Event &e);
        void clear();
        void render();
        void close();
        int getScreenWidth() const {return screenWidth;}
        int getScreenHeight() const {return screenHeight;}
        void updateScore(int player);

    private:
        void loadText(const std::string &score, const int player);
        Scores scores;
        std::string title;
        int screenWidth;
        int screenHeight;
        bool isRunning;
        bool hasInit;
        TTF_Font *font;
};

#endif