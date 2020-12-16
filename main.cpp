#define SDL_MAIN_HANDLED

#include <iostream>
#include <spdlog/spdlog.h>
#include <libconfig.h++>

#include "display.h"
#include "errors.h"

using namespace libconfig;

int main(int, char **) {
    Config cfg;
    try {
        cfg.readFile("settings.cfg");
    } catch (const FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return (EXIT_FAILURE);
    } catch (const ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return (EXIT_FAILURE);
    }
    const Setting &root = cfg.getRoot();
    // Output a list of all books in the inventory.
    try {
        int abc;
        if (root.lookupValue("abc", abc)) {
            std::cout << abc << std::endl;
        }
    } catch (const SettingNotFoundException &nfex) {
        // Ignore.
    }
    spdlog::info("OK, now we are on.");
    try {
        Display disp("Nice");
        bool running = true;
        SDL_Event e;
        disp.add_image("descriptions/Blank_state_map.png");
        while (running) {
            disp.draw();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
            }
        }
        std::cout << "Good going go" << std::endl;
        spdlog::warn("Gone.");
        return 0;
    } catch (const InitError &err) {
        std::cerr << "Error while initializing SDL:  " << err.what()
                  << std::endl;
    }

    return 1;
}
