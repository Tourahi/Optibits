#include <Optibits/GLContext.hpp>

// TODO: MAC/IPHONE

#if !defined(GOSU_IS_IPHONE)

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

Optibits::OpenGLContext::OpenGLContext(bool renderToWindow)
{
  static const auto& window = SDLWindowContext::instance();
  static std::mutex mutex;

  if (currentNestingDepth == 0)
    mLock = std::unique_lock(mutex);

  if (renderToWindow) {
    if (SDL_GL_MakeCurrent(window.window, window.glContext) != 0) {
      throwSdlErr("Could not set current GL context for rendering to the window");
    }
  }
  else if (currentNestingDepth == 0) {
    if (SDL_GL_MakeCurrent(nullptr, window.glContext) != 0
        && SDL_GL_MakeCurrent(window.window, window.glContext) != 0) {
      throwSdlErr("Could not set current GL context");
    }
  }

  ++currentNestingDepth;
}


Optibits::OpenGLContext::~OpenGLContext()
{
  --currentNestingDepth;

  if (mLock)
    SDL_GL_MakeCurrent(nullptr, nullptr);
}

#endif