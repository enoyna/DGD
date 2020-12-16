#define SDL_MAIN_HANDLED

#include <iostream>
#include <spdlog/spdlog.h>
#include <libconfig.h++>

#include "display.h"
#include "errors.h"
#include "conf.h"

using namespace libconfig;

int main(int, char **) {
    ConfigFile c_file("settings.cfg");
    try {
        int abc;
        if (c_file.root().lookupValue("abc", abc)) {
            spdlog::info("Settings abc: {0}", abc);
        }
    } catch (const SettingNotFoundException &nfex) {
        spdlog::error("Setting not found.");
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
        spdlog::warn("Gone.");
    } catch (const InitError &err) {
        spdlog::error("Error while initializing SDL: {0}", err.what());
        return 1;
    }
    return 0;
}
