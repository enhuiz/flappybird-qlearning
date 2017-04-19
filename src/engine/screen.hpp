#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>

#include "utils.hpp"

namespace enhuiz
{
namespace engine
{
class Screen
{

  public:
    Screen(std::string title, int width, int height)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        mWindow = std::unique_ptr<SDL_Window, sdl_deleter>(
            SDL_CreateWindow(
                title.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width,
                height,
                SDL_WINDOW_SHOWN),
            sdl_deleter());

        if (mWindow == nullptr)
        {
            std::cerr << "Window can't be created" << std::endl;
            throw "";
        }

        mRenderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_SOFTWARE),
            sdl_deleter());

        if (mRenderer == nullptr)
        {
            std::cerr << "Renderer can't be created" << std::endl;
            throw "";
        }
    }

    std::shared_ptr<SDL_Renderer> getRenderer() { return mRenderer; }    

    ~Screen()
    {
    }

  private:
    std::unique_ptr<SDL_Window, sdl_deleter> mWindow;
    std::shared_ptr<SDL_Renderer> mRenderer;
};
}
}
#endif