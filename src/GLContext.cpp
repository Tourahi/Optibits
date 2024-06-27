#include <Optibits/GLContext.hpp>

// TODO: MAC/IPHONE

#include <SDL_error.h>
#include <SDL_video.h>
#include <stdexcept>
#include <thread>


namespace
{

  [[noreturn]] void throwSdlErr(const std::string& op)
  {
    throw std::runtime_error(op + ": " + SDL_GetError());
  }

  struct SDLWindowContext : Optibits::Noncopyable
  {
    SDL_Window* window;
    SDL_GLContext glContext;

    SDLWindowContext() {
      static const int inited =  SDL_Init(SDL_INIT_VIDEO);
      if (inited < 0) {
        throwSdlErr("Could not initialize SDL");
      }

      window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 64,
        SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI);

      if (!window) {
        throwSdlErr("Could not create SDL window");
      }

      glContext = SDL_GL_CreateContext(window);
      if (!glContext) {
        SDL_DestroyWindow(window);
        throwSdlErr("Could not create main OpenGL context");
      }
    }

    static SDLWindowContext& instance()
    {
      static SDLWindowContext instance;
      return instance;
    }

  };

  thread_local int currentNestingDepth = 0;
}