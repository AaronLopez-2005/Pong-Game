#include <SDL.h>
#include <iostream>
#include "manager.h"
#include "dot.h"

int main(int argc, char **argv) {

    Manager manager;

    if (!manager.init("Functions", 480, 640)) {
        std::cout << "Could not initialize manager" << std::endl;
        return -1;
    }

    Dot dot(manager.getWindowWidth(), manager.getWindowHeight());
    SDL_Event e;

    while (manager.isRunning()) {
        while(SDL_PollEvent(&e)) {
            manager.handleEvents(e);
            dot.handleEvents(e);
        }

        dot.move();
        manager.clearRender();
        dot.draw(manager.renderer);
        manager.drawToScreen();
    }
    

    manager.close();
    return 0;
}