#include <iostream>

#include "display.h"
#include "errors.h"

#define SDL_MAIN_HANDLED

int main(int, char **) {
    try {
        SDL sdl(SDL_INIT_VIDEO | SDL_INIT_TIMER);
        bool running = true;
        SDL_Event e;
        while (running) {
            sdl.draw();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
            }
        }
        std::cout << "Good going go" << std::endl;
        return 0;
    } catch (const InitError &err) {
        std::cerr << "Error while initializing SDL:  " << err.what()
                  << std::endl;
    }

    return 1;
}
