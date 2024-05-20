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

  }; 

}