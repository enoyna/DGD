#include <SDL2/SDL.h>

class SDL {
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

   public:
    SDL(Uint32 flags = 0);
    virtual ~SDL();
    void draw();
};
