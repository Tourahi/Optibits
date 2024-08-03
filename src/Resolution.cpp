
#include <Optibits/OptiWindow.hpp>
#include <SDL.h>
#include <SDL_video.h>


static SDL_DisplayMode displayMode(const Optibits::OptiWindow* window)
{
  static const struct VideoSubsys : Optibits::Noncopyable
  {
    VideoSubsys() { SDL_InitSubSystem(SDL_INIT_VIDEO); };
    ~VideoSubsys() { SDL_QuitSubSystem(SDL_INIT_VIDEO); };
  } subsys;

  int index = window ? SDL_GetWindowDisplayIndex(window->sdlWindow()) : 0;
  SDL_DisplayMode res;
  SDL_GetDesktopDisplayMode(index, &res);
  return res;
}

int Optibits::screenWidth(const OptiWindow* window) {
  return displayMode(window).w;
}

int Optibits::screenHeight(const OptiWindow* window) {
  return displayMode(window).w;
}
