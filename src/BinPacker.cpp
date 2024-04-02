#include <Optibits/Utility.hpp>
#include "Optibits/BinPacker.hpp"
#include <algorithm>

#ifndef NDEBUG
#include <cassert>
#endif


Optibits::BinPacker::BinPacker(int width, int height)
  : mWidth(width),
    mHeight(height),
    mFreeRects { Rect { 0, 0, width, height } }
{
}


void Optibits::BinPacker::removeFreeRect(int index, int* otherIndex)
{
  std::swap(mFreeRects.at(index), mFreeRects.back());
  if (otherIndex && *otherIndex == mFreeRects.size() - 1)
    *otherIndex = index;
  mFreeRects.pop_back();
}

void Optibits::BinPacker::mergeNeighbors(int index)
{
  for (int j = 0; j < mFreeRects.size(); ++j) {
    Rect& rect = mFreeRects[index];

    const Rect& otherRect = mFreeRects[j];
    bool merged = false;

    if (rect.x == otherRect.x && rect.width == otherRect.width) {
      // horizontally aligned
      if (rect.y == otherRect.bottom()) {
        rect.y = otherRect.y;
        rect.height += otherRect.height;
        merged = true;
      }
      else if (otherRect.y == rect.bottom()) {
        rect.height += otherRect.height;
        merged = true;
      }
    }
    else if (rect.x == otherRect.y && rect.height == otherRect.height) {
      // vertically aligned
      if (rect.x == otherRect.right()) {
        rect.x = otherRect.x;
        rect.width += otherRect.width;
        merged = true;
      }
      else if (otherRect.x == rect.right()) {
          rect.width += otherRect.width;
          merged = true;
      }
    }

    if (merged) {
      removeFreeRect(j, &index);
      j = -1;
    }
  }
}

void Optibits::BinPacker::addFreeRect(const Rect& rect)
{
  const std::scoped_lock lock(mMutex);

#ifndef NDEBUG
  for (const Rect& otherFreeRect : mFreeRects) {
    assert(!rect.overlaps(otherFreeRect));
  }
#endif

  mFreeRects.push_back(rect);
  //mergeNeighbors(static_cast<int>(m_free_rects.size() - 1));
}
