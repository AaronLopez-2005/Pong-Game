#include <iostream>
#include <SDL.h>
#include <vector>
#include "game.h"
#include "paddle.h"
#include "ball.h"

int main(int argc, char **argv) {
    // Creates the game system and initializes it
    Game game(720, 480, "Pong");

    if (!game.init()) {
        std::cout << "Game could not initialize" << std::endl;
        return -1;
    }

    // Creates two paddles
    std::vector<Paddle> paddles;
    for (int i = 0; i < 2; i++) {
        Paddle paddle = {game.getScreenWidth(), game.getScreenHeight()};
        paddles.push_back(paddle);
    }

    // Creates a ball
    Ball ball(game.getScreenWidth(), game.getScreenHeight());
    
    SDL_Event e;

    while(game.running()) {
        while(SDL_PollEvent(&e)) {
            // Game handles quit event
            game.event(e);

            // Paddles handles key events
            for (int i = 0; i < paddles.size(); i++) {
                paddles.at(i).HandleEvent(e);
            }
        }

        // Clears the screen
        game.clear();

        // Moves paddles
        for (int i = 0; i < paddles.size(); i++) {
            paddles.at(i).Move();
        }

        // Checks for collision
        for (int i = 0; i < paddles.size(); i++) {
            if (ball.checkCollision(paddles.at(i).getDimension())) {
                break;
            }
        }

        // Moves the ball
        ball.move();

        // Draws paddles and ball
        for (int i = 0; i < paddles.size(); i++) {
            paddles.at(i).Draw(game.renderer);
        }
        ball.draw(game.renderer);

        game.updateScore(ball.checkOutside());
        // Renders to screen
        game.render();
    }

    game.close();
    return 0;
}