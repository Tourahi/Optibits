#pragma once

#include <compare>
#include <cstdint>
#include <ostream>

namespace Optibits
{

  struct Color
  {
    using Channel = std::uint8_t;
    Channel red = 0, green = 0, blue = 0, alpha = 0;

    Color() = default;

    Color(std::uint32_t argb)
    : red(argb >> 16),
      green(argb >> 8),
      blue(argb >> 0),
      alpha(argb >> 24)
    {
    }

    Color(Channel red, Channel green, Channel blue)
    : red(red),
      green(green),
      blue(blue),
      alpha(255)
    {
    }

    Color withAlpha(Channel newAlpha) const
    {
      Color result = *this;
      result.alpha = newAlpha;
      return result;
    }

    static Color fromHSV(double h, double s, double v);

    double hue() const;

    void setHue(double h);

    double saturation() const;

    void setSaturation(double s);

    double value() const;

    void setValue(double v);

    std::uint32_t argb() const { return alpha << 24 | red << 16 | green << 8 | blue; }
    std::uint32_t bgr() const { return blue << 16 | green << 8 | red; }
    std::uint32_t abgr() const { return alpha << 24 | blue << 16 | green << 8 | red; }

    std::uint32_t gl() const { return *reinterpret_cast<const std::uint32_t*>(this); }
    
    static const Color NONE;
    static const Color BLACK;
    static const Color GRAY;
    static const Color WHITE;

    static const Color AQUA;
    static const Color CYAN;

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color FUCHSIA;

    std::strong_ordering operator<=>(const Color&) const = default;
  };

}