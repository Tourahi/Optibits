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
    IF_SMOOTH = 0,

    IF_TILEABLE_LEFT = 1 << 1,
    IF_TILEABLE_TOP = 1 << 2,
    IF_TILEABLE_RIGHT = 1 << 3,
    IF_TILEABLE_BOTTOM = 1 << 4,
    IF_TILEABLE = IF_TILEABLE_LEFT | IF_TILEABLE_TOP | IF_TILEABLE_RIGHT | IF_TILEABLE_BOTTOM,

    IF_RETRO = 1 << 5
  };

}