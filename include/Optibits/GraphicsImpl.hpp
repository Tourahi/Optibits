#pragma once

#include <Optibits/Bitmap.hpp>
#include <Optibits/Graphics.hpp>
#include <Optibits/Platform.hpp>
#include <algorithm>
#include <cstdint>
#include <list>
#include <vector>

namespace Optibits
{

  //****************************************
  //          RENDER STATE
  //****************************************
  struct RenderState;
  class RenderStateManager;


  enum QueueMode
  {
    QM_RENDER_TO_SCREEN,
    QM_RENDER_TO_TEXTURE,
    QM_RENDER_TO_MACRO
  }

  class Texture;
  class TextChunk;
  class ClipRectStack;

  //****************************************
  //          Drawing OP
  //****************************************
  struct DrawOp;
  class DrawQueue;
  typedef std::list<Transform> Transforms;
  typedef std::list<DrawOpQueue> DrawOpQueueStack;
  class Macro;

  struct ArrayVertex
  {
    float texCoords[2];
    std::uint32_t color;
    float vertices[3];
  }

  template<typename T>
  bool ispToTheleftOfab(T xa, T ya, T xb, T yb, T xp, T yp)
  {
    return (xb - xa) * (yp - ya) - (xp - xa) * (yb - ya) > 0;
  }

  template<typename T, typename C>
  void normalizeCoordinates(T& x1, T& y1, T& x2, T& y2, T& x3, T& y3, C& c3, T& x4, T& y4, C& c4)
  {
    if (ispToTheleftOfab(x1, y1, x2, y2, x3, y3) ==
       ispToTheleftOfab(x2, y2, x3, y3, x4, y4)) {
      std::swap(x3, x4);
      std::swap(y3, y4);
      std::swap(c3, c4);
    }
  }


  void scheduleDrawOp(const DrawOp& op);

  void registerFrame();

  inline std::string escapeMarkup(const std::string& text) {
    auto markup = text;
    for (std::string::size_type pos = 0; pos < markup.length(); ++pos) {
      if (markup[pos] == '&') {
        markup.replace(pos, 1, "&amp;");
      }
      else if (markup[pos] == '<') {
        markup.replace(pos, 1, "&lt;");
      }
    }
    return markup;
  }
}