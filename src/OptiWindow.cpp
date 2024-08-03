#include <Optibits/Optibits.hpp>
#include <Optibits/GLContext.hpp>

// STD
#include <algorithm>

struct Optibits::OptiWindow::Impl : private Optibits::Noncopyable
{
  bool fullscreen = false;
  bool resizable = false; 
  bool resizing = false; 


  enum {
    CLOSED, OPEN, CLOSING
  } state
    = CLOSED;

  std::unique_ptr<Input> input;
};

Optibits::OptiWindow::OptiWindow(int width, int height, unsigned windowFlags, double updateIntrv)
  : mImpl(new Impl) 
{

}

SDL_Window* Optibits::OptiWindow::sdlWindow() const
{
  return OpenGLContext::sharedSdlWindow();
}

void Optibits::OptiWindow::setBorderless(bool borderless)
{
  SDL_SetWindowBordered(sdlWindow(), borderless ? SDL_FALSE : SDL_TRUE);
}

void Optibits::OptiWindow::setResizable(bool resizable)
{
  mImpl->resizable = resizable;
  SDL_SetWindowResizable(sdlWindow(), resizable ? SDL_FALSE : SDL_TRUE);
}


void Optibits::OptiWindow::resize(int width, int height, int fullscreen)
{
  mImpl->fullscreen = fullscreen;

  int actualWidth = width;
  int actualHeight = height;
  double scaleFactor = 1.0;
  double blackBarWidth = 0;
  double blackBarHeight = 0;


}

