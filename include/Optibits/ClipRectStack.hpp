#pragma once

#include <Optibits/Utility.hpp>
#include <Optibits/GraphicsImpl.hpp>
// STD
#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>


namespace Optibits
{
  class ClipRectStack
  {
    std::vector<Rect> mStack;
    std::optional<Rect> mEffectiveRect;

  public:
    void clear();
    void push(const Rect& rect);
    void pop();

    const std::optional<Rect>& effectiveRect() const { return mEffectiveRect; }
  }
}
