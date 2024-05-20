#include "Optibits/Keyboard.hpp"
#include <Optibits/Platform.hpp>
#include <SDL_error.h>

#if !defined(OPTIBITS_IPHONE)

#include <Optibits/Input.hpp>
#include <Optibits/Utility.hpp>

#include <SDL.h>
#include <utf8proc.h>

#include <cstdlib>
#include <algorithm>
#include <array>
#include <stdexcept>
using namespace std;


static void requireSdlVideo()
{
  static const int initialized = SDL_Init(SDL_INIT_VIDEO);
  if (initialized < 0)
    throw std::runtime_error(SDL_GetError());
}

static const unsigned NUM_BUTTONS_PER_GAMEPAD =
  (Optibits::GP_RANGE_END - Optibits::GP_RANGE_BEGIN + 1 - 4) / (Optibits::NUM_GAMEPADS + 1) - 3;

static const unsigned NUM_AXES_PER_GAMEPAD = Optibits::NUM_AXES / (Optibits::NUM_GAMEPADS + 1);
static const unsigned NUM_BUTTONS = Optibits::GP_RANGE_END + 1;

static array<bool, NUM_BUTTONS> buttonStates = {false};
static array<double, NUM_AXES_PER_GAMEPAD * (Optibits::NUM_GAMEPADS + 1)> axisStates = {0.0};
static vector<shared_ptr<SDL_Joystick>> openJoysticks;
static vector<shared_ptr<SDL_GameController>> openGameControllers;

// -1 empty.
static array<int, Optibits::NUM_GAMEPADS> gamepadSlots = {-1, -1, -1, -1};

struct Optibits::Input::Impl : private Optibits::Noncopyable
{
  
}




#endif