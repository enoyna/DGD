#include <SDL.h>

class Display {
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

   public:
    Display(Uint32 flags = 0);
    virtual ~Display();
    void draw();
};
