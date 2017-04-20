#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace enhuiz
{
namespace engine
{
struct sdl_deleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
    void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
};
}
}

#endif