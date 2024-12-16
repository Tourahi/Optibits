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


bool Optibits::OptiWindow::resizable() const
{
  return mImpl->resizable;
}

void Optibits::OptiWindow::resize(int width, int height, int fullscreen)
{
  mImpl->fullscreen = fullscreen;

  int actualWidth = width;
  int actualHeight = height;
  double scaleFactor = 1.0;
  double blackBarWidth = 0;
  double blackBarHeight = 0;

  if (fullscreen) {
    actualWidth = Optibits::screenWidth();
    actualHeight = Optibits::screenHeight();

    if (resizable()) {
      width = actualWidth;
      height = actualHeight;
    }
    else {
      // scale window to fill the desktop res
      double scaleX = 1.0 * actualWidth / width;
      double scaleY = 1.0 * actualHeight / height;
      scaleFactor = std::min(scaleX, scaleY);

      // add black bars to preserve aspect ratio if needed
      if (scaleX < scaleY) {
        blackBarHeight = (actualHeight / scaleX - height) / 2;
      }
      else if (scaleY < scaleX) {
        blackBarWidth = (actualWidth / scaleY - width) / 2;
      }
    }
  }
  else {
    int maxWidth = Optibits::availableWidth(this);
    int maxHeight = Optibits::availableHeight(this);

    if (resizable()) {
      width = actualWidth = std::min(width, maxWidth);
      height = actualHeight = std::min(height, maxHeight);
    }
    else if (width > maxWidth || height > maxHeight) {
      scaleFactor = std::min(1.0 * maxWidth / width, 1.0 * maxHeight / height);
      actualWidth = static_cast<int>(width * scaleFactor);
      actualHeight = static_cast<int>(height * scaleFactor);
    }
  }


}

