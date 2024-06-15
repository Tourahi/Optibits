#include <Optibits/GLContext.hpp>

// TODO: MAC/IPHONE

#include <SDL_error.h>
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

    }


    static SDLWindowContext& instance()
    {
      static SDLWindowContext instance;
      return instance;
    }


  };
}