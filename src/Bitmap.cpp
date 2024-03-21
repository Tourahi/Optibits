#include <Optibits/Bitmap.hpp>
#include <Optibits/GraphicsBase.hpp>
#include <algorithm>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <utility>


Optibits::Bitmap::Bitmap(int width, int height, Color c)
  : mWidth(width),
    mHeight(height)
{

  if (width < 0 || height < 0) {
    throw std::invalid_argument("Negative Optibits::Bitmap size.");
  }

  if (height != 0 && width > std::numeric_limits<int>::max() / height) {
    throw std::invalid_argument("Optibits::Bitmap size out of bounds.");
  }

  const int size = width * height;
  mPixels = Buffer(size * sizeof(Color));
  std::fill_n(data(), size, c);
}