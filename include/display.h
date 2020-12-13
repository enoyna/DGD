#include <SDL.h>

class Display {
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

   public:
    Display(Uint32 flags = SDL_INIT_EVERYTHING);
    virtual ~Display();
    void draw();
};
