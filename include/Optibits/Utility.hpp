#pragma once

#include <Optibits/Platform.hpp>
#include <string>
#include <string_view>
#include <vector>

namespace Optibits
{

  bool hasExtension(std::string_view filename, std::string_view ext);

  std::vector<std::string> userLanguages();

  std::u32string utf8ToComposedUtc4(std::string_view utf8);

#ifdef OPTIBITS_WIN
  std::wstring utf8ToUtf16(const std::string& utf8);
  std::string utf16ToUtf8(const std::string& utf8);
#endif


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