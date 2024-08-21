#pragma once

#include <Optibits/Fwd.hpp>
#include <Optibits/Color.hpp>
#include <Optibits/GraphicsBase.hpp>
#include <Optibits/Utility.hpp>
// STD
#include <cstdint>
#include <memory>

namespace Optibits
{

  const unsigned MAX_TEXTURE_SIZE = 1024;

  struct GLTexInfo
  {
    std::uint32_t texName;
    double left, right, top, bottom;
  };

  class Drawable : private Noncopyable
  {
  public:
    Drawable() = default;
    virtual ~Drawable() = default;

    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual int draw(double x1, double y1, Color c1, //
                    double x2, double y2, Color c2, //
                    double x3, double y3, Color c3, //
                    double x4, double y4, Color c4, //
                    ZPos z, BlendMode mode) const
                    = 0;

    virtual const GLTexInfo* glTexInfo() const = 0;

    virtual Bitmap toBitMap const = 0;

    virtual std::unique_ptr<Drawable> subimage(const Rect& rect) const = 0;

    virtual void insert(const Bitmap& bitmap, int x, int y) = 0;

  };
}