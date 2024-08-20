#include <Optibits/Texture.hpp>
#include <Optibits/Bitmap.hpp>
#include <Optibits/Platform.hpp>
#include <Optibits/GLContext.hpp>
#include <Optibits/TexChunk.hpp>

#include <SDL_opengl.h>
#include <stdexcept>

Optibits::Texture::Texture(int width, int height, bool retro)
  : mBinPacker(width, height),
    mTexName(0),
    mRetro(retro)
{
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("Optibits::Texture must not be empty.");
  }

  const OpenGLContext currentContext;

  // create texture name.
  glGenTextures(1, &mTexName);

  if (mTexName == static_cast<GLuint>(-1)) {
    throw std::runtime_error("Failed to allocate OpenGL texture");
  }

  // Create empty texture.
  glBindTexture(GL_TEXTURE_2D, mTexName);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mBinPacker.width(), mBinPacker.height(), 
    0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  if (retro) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

#ifdef GL_CLAMP_TO_EDGE
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#else
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
#endif
}
