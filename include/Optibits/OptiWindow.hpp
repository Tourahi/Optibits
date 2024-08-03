#pragma once


#include <Optibits/Fwd.hpp>
#include <Optibits/Input.hpp>
#include <Optibits/Platform.hpp>
#include <Optibits/Utility.hpp>
#include <memory>
#include <string>

struct SDL_Window;

namespace Optibits
{
  
  enum WindowFlags
  {
    WF_WINDOWED,
    WF_FULLSCREEN = 1,
    WF_RESIZABLE = 2,
    WF_BORDERLES = 3
  };

  
  class OptiWindow : private Noncopyable
  {

    struct Impl;
    std::unique_ptr<Impl> mImpl;

  public:

    OptiWindow(int width, int height, unsigned windowFlags = WF_WINDOWED,
      double updateIntrv = 16.666666);

    virtual ~OptiWindow();

    int width() const;
    int height() const;
    bool fullscreen() const;
    void resize(int width, int height, int fullscreen);

    bool borderless() const;
    void setBorderless(bool borderless);

    bool resizable() const;
    void setResizable(bool resizable);

#ifndef OPTIBITS_IPHONE
    SDL_Window* sdlWindow() const;
#endif
  };

  /* Resolution */
  
  int screenWidth(const OptiWindow* window = nullptr);
  int screenHeight(const OptiWindow* window = nullptr);
  
  /* End Resolution */

}