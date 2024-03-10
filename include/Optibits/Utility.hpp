#pragma once

#include <Optibits/Platform.hpp>
#include <string>
#include <string_view>
#include <vector>

namespace Optibits
{

  bool has_extension(std::string_view filename, std::string_view ext);

  std::vector<std::string> user_languages();

  std::u32string utf8_to_composed_utc4(std::string_view utf8);


  class Noncopyable
  {
  protected:
    Noncopyable() = default;
    ~Noncopyable() = default;

  public:
    Noncopyable(const Noncopyable& other) = delete;
    Noncopyable& operator=(const Noncopyable& other) = delete;

    Noncopyable(Noncopyable&& other) = delete;
    Noncopyable& operator=(Noncopyable&& other) = delete;
  };

  // Int based rect. <Internal-use>
  struct Rect
  {
    int x = 0, y = 0;
    int width = 0, height = 0;  

    int right() const { return x + width; }
    int bottom() const { return y + height; }

    bool empty() const { return width <= 0 || height <=  0; }

    template <typename  T> static Rect  covering(const T& obj)
    {
      return Rect { .x = 0, .y = 0, .width = obj.width(), .height = obj.height() };
    }

    bool overlaps(const Rect& other) const;
    bool contains(const Rect& other) const;

    void clipTo(const Rect& boundingBox, int*  adjustX = nullptr, int*  adjustY = nullptr);
    
    bool operator==(const Rect& other) const = default;
  };
}