#include <string>
#include <thread>
#include <memory>
#include <algorithm>
#include <list>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"

namespace flappyql
{
class Engine
{
  private:
    struct sdl_deleter
    {
        void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
        void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
        void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
    };

    class Screen
    {
      public:
        Screen(std::string title, int width, int height) : window()
        {
            SDL_Init(SDL_INIT_EVERYTHING);

            window = std::unique_ptr<SDL_Window, sdl_deleter>(
                SDL_CreateWindow(
                    title.c_str(),
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    width,
                    height,
                    SDL_WINDOW_SHOWN),
                sdl_deleter());

            if (window == nullptr)
            {
                std::cerr << "Window can't be created" << std::endl;
                throw "";
            }

            renderer = std::unique_ptr<SDL_Renderer, sdl_deleter>(
                SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE),
                sdl_deleter());

            if (renderer == nullptr)
            {
                std::cerr << "Renderer can't be created" << std::endl;
                throw "";
            }

            event = std::unique_ptr<SDL_Event>(new SDL_Event());
        }

        ~Screen()
        {
        }

        const std::unique_ptr<SDL_Renderer, sdl_deleter> &getRenderer() const
        {
            return renderer;
        }

        const std::unique_ptr<SDL_Event> &getEvent() const
        {
            return event;
        }

      private:
        std::unique_ptr<SDL_Window, sdl_deleter> window;
        std::unique_ptr<SDL_Renderer, sdl_deleter> renderer;
        std::unique_ptr<SDL_Event> event;
    };

  public:
    class Transform
    {
      public:
        Vector3 position;
    };

    class Sprite
    {
      public:
        Sprite(std::string filename)
        {
            texture = std::unique_ptr<SDL_Texture, sdl_deleter>(IMG_LoadTexture(
                nullptr,
                filename.c_str()));
        }

        const std::unique_ptr<const SDL_Texture, sdl_deleter> &getTexture() const
        {
            return texture;
        }

      private:
        std::unique_ptr<SDL_Texture, sdl_deleter> texture;
    };

    class GameObject
    {
        friend class Engine;

      public:
        GameObject() = default;
        ~GameObject() {}

        void setActive(bool active)
        {
            this->active = active;
        }

        void setSprite(std::string filename)
        {
            sprite = std::unique_ptr(new Sprite(filename));
        }

        void render(const std::unique_ptr<SDL_Renderer, sdl_deleter> &renderer)
        {
            if (sprite != nullptr)
            {
                SDL_Rect rect
                {
                    transform.position.x,
                        transform.position.y,
                        sprite->texture->getTexture().w,
                        sprite->texture->getTexture().h,
                }
                SDL_RenderCopy(renderer, sprite->text);
            }
        }

        void update()
        {
        }

        void start()
        {
        }

      protected:
        bool active = false;
        std::string name = "";
        Transform transform;
        std::unique_ptr<Sprite> sprite;
    };

    Engine(std::string title, int width, int height) : screen(title, width, height)
    {
    }

    void update()
    {
        for (auto gameObject : gameObjects)
        {
            if (gameObject->active)
            {
                gameObject->update();
            }
        }
    }

    void render()
    {
        SDL_RenderClear(screen.getRenderer().get());
        for (auto gameObject : gameObjects)
        {
            if (gameObject->active)
            {
                gameObject->render();
            }
        }
        SDL_RenderPresent(screen.getRenderer().get());
    }

    void pollEvent()
    {
        SDL_PollEvent(screen.getEvent().get());
        if (screen.getEvent()->type == SDL_QUIT)
        {
            running = false;
        }
    }

    void run()
    {
        running = true;
        while (running)
        {
            pollEvent();
            update();
            render();
        }
    }

    void addGameObject(const std::shared_ptr<GameObject> &gameObject)
    {
        gameObjects.push_back(gameObject);
        gameObject->start();
    }

    void removeGameObject(const std::shared_ptr<GameObject> &gameObject)
    {
        gameObjects.remove(gameObject);
    }

  private:
    bool running = false;
    std::list<std::shared_ptr<GameObject>> gameObjects;
    Screen screen;
};
}