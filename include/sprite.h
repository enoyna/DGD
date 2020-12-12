#include <SDL.h>

class Sprite {
    SDL_Surface *m_surface;

   public:
    Sprite();
    virtual ~Sprite();
    void draw();
}
