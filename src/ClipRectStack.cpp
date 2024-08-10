#include "Optibits/Utility.hpp"
#include <Optibits/ClipRectStack.hpp>
#include <stdexcept>

void Optibits::ClipRectStack::clear()
{
  mStack.clear();
  mEffectiveRect = std::nullopt;
}


void Optibits::ClipRectStack::push(const Rect& rect)
{
  mStack.push_back(rect);
  if (mEffectiveRect) {
    mEffectiveRect->clipTo(rect);
  }
  else {
    mEffectiveRect = rect;
  }
}


void Optibits::ClipRectStack::pop()
{
  if (mStack.empty()) {
    throw std::logic_error("ClipRectStack is empty");    
  }
  mStack.pop_back();

  // The clip rect is the intersection of all active clip rects
  mEffectiveRect = std::nullopt;
  for (const auto& rect : mStack) {
    if (mEffectiveRect) {
      mEffectiveRect->clipTo(rect);
    }
    else {
      mEffectiveRect = rect;
    }
  }
}
