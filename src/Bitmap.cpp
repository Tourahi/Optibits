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

Optibits::Bitmap::Bitmap(int width, int height, Optibits::Buffer&& buffer)
  : mWidth(width),
    mHeight(height),
    mPixels(std::move(buffer))
{
  int pixels = width * height;
  if (static_cast<std::size_t>(pixels) * sizeof(Color) != mPixels.size()) {
    throw std::length_error("Optibits::Bitmap given Optibits::Buffer of wrong size, expected "
      + std::to_string(pixels * sizeof(Color)) + ", given "
      + std::to_string(mPixels.size()));
  }
}

void Optibits::Bitmap::resize(int width, int height, Color c)
{
  if (width != mWidth || height != mHeight) {
    Bitmap temp(width, height, c);
    std::swap(*this, temp);
  }
}

void Optibits::Bitmap::blendPixel(int x, int y, Color c)
{
  if (c.alpha == 0) {
    return;
  }

  Color& out = pixel(x, y);
  if (out.alpha == 0 || c.alpha == 255) {
    out = c;
    return;
  }

  int invAlpha = out.alpha * (255 - c.alpha) / 255;

  out.alpha = (c.alpha + invAlpha);
  out.red = ( (c.red *  c.alpha + out.red * invAlpha) / out.alpha );
  out.green = ( (c.green *  c.alpha + out.green * invAlpha) / out.alpha );
  out.blue = ( (c.blue *  c.alpha + out.blue * invAlpha) / out.alpha );
}

void Optibits::Bitmap::insert(const Bitmap& source, int x, int y, Rect sourceRect) 
{
  if (&source == this) {
    throw std::invalid_argument("Optibits::Bitmap::insert cannot copy parts of itself.");
  }

  sourceRect.clipTo(Rect::covering(source), &x, &y);

  Rect targetRect = { .x = x, .y = y, .width = sourceRect.width, .height = sourceRect.height };

  targetRect.clipTo(Rect::covering(*this), &sourceRect.x, &sourceRect.y);

  Color* targetPtr = &pixel(targetRect.x, targetRect.y);
  const Color* sourcePtr = &source.pixel(sourceRect.x, sourceRect.y);

  if (width() == source.width() && width() == targetRect.width) {
    const int size = targetRect.width * targetRect.height;
    std::memcpy(targetPtr, sourcePtr, static_cast<std::size_t>(size) * sizeof(Color));
  }
  else {
    for (int row = 0; row < targetRect.height; ++row) {
      std::memcpy(targetPtr, sourcePtr, targetRect.width * sizeof(Color));
      targetPtr += width();
      sourcePtr += source.width();
    }
  }
}

bool Optibits::Bitmap::operator==(const Optibits::Bitmap& other) const
{
  int pixels = width() * height();
  return pixels == other.width() * other.height()
    && std::equal(data(), data() + pixels, other.data());
}


void Optibits::Bitmap::applyColorKey(Color key)
{
  const int pixels = width() * height();
  Color* begin = data();
  Color* end = begin + pixels;

  for (Color* c = begin; c != end;) {
    for (int x = 0; x < width(); ++x, ++c) {
      if (*c != key) {
        continue;
      }

      unsigned neighbors = 0, red = 0, green = 0, blue = 0;

      const auto visit = [&](const Color* neighbor) {
        if (neighbor >= begin && neighbor < end && *neighbor != key && neighbor->alpha) {
          ++neighbors;
          red += neighbor->red;
          green += neighbor->green;
          blue += neighbor->blue;
        }
      };

      if (x != 0) {
        visit(c - width() - 1);
        visit(c - 1);
        visit(c + width() - 1);
      }
      visit(c - width());
      visit(c + width());

      if (x != width() - 1) {
        visit(c + width() + 1);
        visit(c + 1);
        visit(c - width() + 1);
      }

      *c = Color::NONE;

      if(neighbors > 0) {
        c->red = red / neighbors;
        c->green = green / neighbors;
        c->blue = blue / neighbors;
      }
    }
  }
}


Optibits::Bitmap Optibits::applyBorderFlags(unsigned imageFlags, const Bitmap& source, Rect sourceRect)
{
  Optibits::Bitmap result(sourceRect.width + 2, sourceRect.height + 2);
  result.insert(source, 1, 1, sourceRect);

  const Rect top { sourceRect.x, sourceRect.y, sourceRect.width, 1 };
  result.insert(source, 1, 0, top);
  const Rect bottom { sourceRect.x, sourceRect.bottom() - 1, sourceRect.width, 1 };
  result.insert(source, 1, result.height() - 1, bottom);
  const Rect left { sourceRect.x, sourceRect.y, 1, sourceRect.height };
  result.insert(source, 0, 1, left);
  const Rect right { sourceRect.right() - 1, sourceRect.y, 1, sourceRect.height };
  result.insert(source, result.width() - 1, 1, right);

  const Rect topLeft { sourceRect.x, sourceRect.y, 1, 1 };
  result.insert(source, 0, 0, topLeft);
  const Rect topRight { sourceRect.right() - 1, sourceRect.y, 1, 1 };
  result.insert(source, result.width() - 1, 0, topRight);
  const Rect bottomLeft { sourceRect.x, sourceRect.bottom() - 1, 1, 1 };
  result.insert(source, 0, result.height() - 1, bottomLeft);
  const Rect bottomRight { sourceRect.right() - 1, sourceRect.bottom() - 1, 1, 1 };
  result.insert(source, result.width() - 1, result.height() - 1, bottomRight);

  if ((imageFlags & IF_TILEABLE_TOP) == 0) {
    for (int x = 0; x < result.width(); ++x) {
      result.pixel(x, 0).alpha = 0;
    }
  }
  if ((imageFlags & IF_TILEABLE_BOTTOM) == 0) {
    const int y = result.height() - 1;
    for (int x = 0; x < result.width(); ++x) {
      result.pixel(x, y).alpha = 0;
    }
  }
  if ((imageFlags & IF_TILEABLE_LEFT) == 0) {
    for (int y = 0; y < result.height(); ++y) {
      result.pixel(0, y).alpha = 0;
    }
  }
  if ((imageFlags & IF_TILEABLE_RIGHT) == 0) {
    const int x = result.width() - 1;
    for (int y = 0; y < result.height(); ++y) {
      result.pixel(x, y).alpha = 0;
    }
  }

  return result;
}

