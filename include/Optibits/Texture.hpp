#pragma once

#include <Optibits/Utility.hpp>
#include <Optibits/Fwd.hpp>
#include <Optibits/BinPacker.hpp>
#include <Optibits/TexChunk.hpp>
#include <cstdint>
#include <memory>

namespace Optibits
{
  class Texture : public std::enable_shared_from_this<Texture>, private Noncopyable
  {
    BinPacker mBinPacker;
    std::uint32_t mTexName;
    const bool mRetro;
  
  public:
    Texture(int width, int height, bool retro);
    ~Texture();

    int width() const { return mBinPacker.width(); }
    int height() const { return mBinPacker.height(); }
    std::uint32_t texName() const { return mTexName; }
    bool retro() const { return mRetro; }

  };
}