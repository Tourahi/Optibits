#pragma once

#include <Optibits/Platform.hpp>
#include <Optibits/Utility.hpp>
#include <mutex>
#include <memory>
#include <vector>

namespace Optibits
{
  

  class BinPacker : private Noncopyable
  {
    const int mWidth, mHeight;
    std::vector<Rect> mFreeRects;
    std::mutex mMutex;


  public:
    BinPacker(int width, int height);

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    std::shared_ptr<const Rect> alloc(int width, int height);

    void addFreeRect(const Rect& rect);

  private:

    const Rect* bestFreeRect(int width, int height) const;

    void removeFreeRect(int index, int* otherIndex = nullptr);

    void mergeNeighbors(int index);

  };



}
