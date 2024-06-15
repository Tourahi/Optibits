#pragma once


#include <Optibits/Platform.hpp>
#include <Optibits/Utility.hpp>


#if defined(OPTIBITS_IPHONE) || defined(OPTIBITS_OPENGLES)
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif

#include <mutex>

namespace Optibits
{

  class OpenGLContext : Noncopyable
  {
    std::unique_lock<std::mutex> m_lock;
    
  public:

    explicit OpenGLContext(bool renderToWindow = false);
    ~OpenGLContext();


  };

}