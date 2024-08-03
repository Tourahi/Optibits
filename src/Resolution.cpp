
#include <Optibits/OptiWindow.hpp>
#include <SDL.h>

#ifndef OPTIBITS_IPHONE

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

int Optibits::screenWidth(const OptiWindow* window)
{
  return displayMode(window).w;
}

int Optibits::screenHeight(const OptiWindow* window)
{
  return displayMode(window).w;
}


#ifdef OPTIBITS_X

static SDL_Rect maxWindowSize(const Optibits::OptiWindow* window)
{
  static const struct VideoSubsys : Optibits::Noncopyable
  {
    VideoSubsys() { SDL_InitSubSystem(SDL_INIT_VIDEO); };
    ~VideoSubsys() { SDL_QuitSubSystem(SDL_INIT_VIDEO); };
  } subsys;

  int index = window ? SDL_GetWindowDisplayIndex(window->sdlWindow()) : 0;
  SDL_Rect rect;
  SDL_GetDisplayUsableBounds(index, &rect);

  if (window) {
    int top, left, bottom, right;
    SDL_GetWindowBordersSize(window->sdlWindow(), &top, &left, &bottom, &right);
    rect.w -= left + right;
    rect.h -= top + bottom;
  }

  return rect;
}

#endif

int availableWidth(const Optibits::OptiWindow* window)
{
  return maxWindowSize(window).w;
}

int availableHeight(const Optibits::OptiWindow* window)
{
  return maxWindowSize(window).h;
}


#endif