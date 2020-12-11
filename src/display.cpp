#include "display.h"
#include "errors.h"

#include <SDL.h>
#include <SDL_events.h>

#include <exception>
#include <iostream>
#include <string>

SDL::SDL(Uint32 flags) {
    if (SDL_Init(flags) != 0) throw InitError();

    if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &m_window,
                                    &m_renderer) != 0)
        throw InitError();
}

SDL::~SDL() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void SDL::draw() {
    // Clear the window with a black background
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Show the window
    SDL_RenderPresent(m_renderer);

    int rgb[] = {
        203, 203, 203,  // Gray
        254, 254, 31,   // Yellow
        0,   255, 255,  // Cyan
        0,   254, 30,   // Green
        255, 16,  253,  // Magenta
        253, 3,   2,    // Red
        18,  14,  252,  // Blue
        0,   0,   0     // Black
    };

    SDL_Rect colorBar;
    colorBar.x = 0;
    colorBar.y = 0;
    colorBar.w = 80;
    colorBar.h = 480;

    for (int i = 0; i != sizeof rgb / sizeof *rgb; i += 3, colorBar.x += 90) {
        SDL_SetRenderDrawColor(m_renderer, rgb[i], rgb[i + 1], rgb[i + 2], 255);
        SDL_RenderFillRect(m_renderer, &colorBar);
        SDL_RenderPresent(m_renderer);
        // SDL_Delay(5);
    }
}
