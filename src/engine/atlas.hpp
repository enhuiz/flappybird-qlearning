#ifndef ATLAS_HPP
#define ATLAS_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.hpp"
#include "sprite.hpp"

namespace enhuiz
{
namespace engine
{
class Atlas
{
  public:
    Atlas(std::string imagepath, std::string descpath, std::shared_ptr<SDL_Renderer> renderer) 
    {
        mTexture = std::shared_ptr<SDL_Texture>(
            IMG_LoadTexture(renderer.get(), imagepath.c_str()),
            sdl_deleter());

        if (mTexture == nullptr)
        {
            std::cerr << "Texture not loaded" << std::endl;
            throw "";
        }

        SDL_QueryTexture(mTexture.get(), NULL, NULL, &mWidth, &mHeight);

        std::ifstream ifs(descpath, std::ios::in);

        if (!ifs)
        {
            std::cerr << "Description file not loaded" << std::endl;
            throw "";
        }

        try
        {
            std::string line;
            while (std::getline(ifs, line))
            {
                std::stringstream ss;
                ss << line;

                std::string name;
                int w, h;
                float x, y;

                ss >> name >> w >> h >> x >> y;

                x *= mWidth;
                y *= mHeight;

                mDesc[name] = SDL_Rect{static_cast<int>(x), static_cast<int>(y), w, h};
            }
        }
        catch (...)
        {
            std::cerr << "Parse description file error" << std::endl;
            throw "";
        }
    }

    std::shared_ptr<SDL_Texture> getTexture()
    {
        return mTexture;
    }

    SDL_Rect getRect(std::string spriteName)
    {
        return mDesc[spriteName];
    }

  private:
    int mWidth, mHeight;

    std::shared_ptr<SDL_Texture> mTexture;
    std::map<std::string, SDL_Rect> mDesc;
};
}
}

#endif