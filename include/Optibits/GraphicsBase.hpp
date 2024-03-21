#pragma once

namespace Optibits
{
  typedef double ZPos;

  enum BlendMode
  {
    BM_DEFAULT,
    BM_INTERPOLATE = BM_DEFAULT,
    BM_ADD,
    BM_MULTIPLY
  };

  enum FontFlags
  {
    FF_BOLD = 1,
    FF_ITALIC = 2,
    FF_UNDERLINE = 4,
    FF_COMBINATIONS = 8
  };

  enum Alignment
  {
    AL_LEFT,
    AL_RIGHT,
    AL_CENTER,
    AL_JUSTIFY
  };

  enum ImageFlags
  {
    IF_SMOOTH = 0
  };

}