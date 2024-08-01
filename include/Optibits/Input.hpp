#pragma once

#include <Optibits/Keyboard.hpp>
#include <Optibits/Platform.hpp>
#include <Optibits/Utility.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace Optibits 
{

  class Input : private Noncopyable
  {

    struct Impl;
    std::unique_ptr<Impl> pimpl;

  public:
  #ifdef OPTIBITS_IPHONE
    Input(void* view, float upate_intrv);
    void feedTouchEvent(); // TODO
  #else
    explicit Input(void* window);
    bool feedSdlEvent(void* event);
  #endif

    ~Input();

    static std::string idToChar(Key key);
    static Key charToId(std::string ch);
    static std::string keyName(Key key);

    static std::string gamepadName(int idx);

    static bool down(Key key);

    static double axis(Key key);

    double mouseX() const;
    double mouseY() const;

    void setMousePosition(double x, double y);


    void update();

    std::function<void (Key)> onButtonDown, onButtonUp;

  }; 

}