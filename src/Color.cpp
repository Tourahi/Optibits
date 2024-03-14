#include <Optibits/Color.hpp>
#include <Optibits/Math.hpp>
#include <algorithm>
#include <cmath>
#include <iomanip>


Optibits::Color Optibits::Color::fromHSV(double h, double s, double v)
{

  h = normalizeAngle(h);

  s = std::clamp(s, 0.0, 1.0);
  v = std::clamp(v, 0.0, 1.0);

  const auto toChannel = [](double d) { return static_cast<Channel>(std::round(255.0 *d)); };

  int sector = static_cast<int>(h / 60);
  double remainder = h / 60 - sector;

  Channel p = toChannel(v * (1 - s));
  Channel q = toChannel(v * (1 - s * remainder));
  Channel t = toChannel(v * (1 - s * (1 - remainder)));

  switch (sector) {
  case 0:
    return Color { toChannel(v), t, p };
  case 1:
    return Color { q, toChannel(v), p };
  case 2:
    return Color { p, toChannel(v), t };
  case 3:
    return Color { p, q, toChannel(v) };
  case 4:
    return Color { t, p, toChannel(v) };
  default:
    return Color { toChannel(v), p, q };
  }

}

double Optibits::Color::hue() const
{

  double max = std::max({ red, green, blue });
  double min = std::min({ red, green, blue });

  if (min == max) {
    return 0;
  }

  double factor = 60 / (max - min);

  if (green == max) {
    return (blue - red) * factor + 120;
  } else if (blue == max) {
    return (red - green) * factor + 240;
  } else if (blue > green) {
    return (green - blue) * factor + 360;
  } else {
    return (green - blue) * factor + 0;
  }
}

void Optibits::Color::setHue(double h)
{
  *this = fromHSV(h, saturation(), value()).withAlpha(alpha);
}

double Optibits::Color::saturation() const
{
  double max = std::max({ red, green, blue });

  if (max == 0) {
    return 0;
  }

  double min = std::min({ red, green, blue });

  return 1 - (min / max);
}

void Optibits::Color::setSaturation(double s)
{
  *this = fromHSV(hue(), s, value()).withAlpha(alpha);
}

double Optibits::Color::value() const
{
  return std::max({ red, green, blue }) / 255.0;
}

void Optibits::Color::setValue(double v)
{
  *this = fromHSV(hue(), saturation(), v).withAlpha(alpha);
}

const Optibits::Color Optibits::Color::NONE { 0x00'000000 };
const Optibits::Color Optibits::Color::BLACK { 0, 0, 0 };
const Optibits::Color Optibits::Color::GRAY { 128, 128, 128 };
const Optibits::Color Optibits::Color::WHITE { 255, 255, 255 };

const Optibits::Color Optibits::Color::AQUA { 0, 255, 255 };
const Optibits::Color Optibits::Color::RED { 255, 0, 0 };
const Optibits::Color Optibits::Color::GREEN { 0, 255, 0 };
const Optibits::Color Optibits::Color::BLUE { 0, 0, 255 };
const Optibits::Color Optibits::Color::YELLOW { 255, 255, 0 };
const Optibits::Color Optibits::Color::FUCHSIA { 255, 0, 255 };
const Optibits::Color Optibits::Color::CYAN { 0, 255, 255 };

