#pragma once

#include <Optibits/Buffer.hpp>
#include <Optibits/Color.hpp>
#include <Optibits/Utility.hpp>
#include <string>
#include <string_view>

namespace Optibits
{

  class Bitmap
  {
    int mWidth = 0, mHeight = 0;
    Buffer mPixels;

  public:
    
    Bitmap() = default;

    Bitmap(int width, int height, Color c = Color::NONE);

    Bitmap(int width, int height, Optibits::Buffer&& buffer);

    int width() const { return mWidth; };
    int height() const { return mHeight; };

    void resize(int width, int height, Color c = Color::NONE);


    const Color* data() const { return reinterpret_cast<const Color*>(mPixels.data()); }
    Color* data() { return reinterpret_cast<Color*>(mPixels.data()); }

    const Color& pixel(int x, int y) const { return data()[y * mWidth + x]; }
    Color& pixel(int x, int y) { return data()[y * mWidth + x]; }

    // https://en.wikipedia.org/wiki/Alpha_compositing
    void blendPixel(int x, int y, Color c);

    void insert(const Bitmap& source, int x, int y, Rect sourceRect);

    void applyColorKey(Color key);

    bool operator==(const Bitmap&) const;

  };
  
}
