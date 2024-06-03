#include <Optibits/Platform.hpp>

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

  
  Input& input;
  SDL_Window* window;

  double mouseX, mouseY;
  double mouseScaleX = 1;
  double mouseScaleY = 1;
  double mouseOffsetX = 0;
  double mouseOffsetY = 0;

  Impl(Input& input, SDL_Window* window)
  : input(input), window(window)
  {
    requireSdlVideo();
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
  }

  ~Impl()
  {
    openJoysticks.clear();
    openGameControllers.clear();

    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
  }

  void updateMousePosition()
  {
    int x, y, windowX, windowY;
    SDL_GetWindowPosition(window, &windowX, &windowY);
    SDL_GetGlobalMouseState(&x, &y);
    mouseX = x - windowX;
    mouseY = y - windowY;
  }

  void setMousePosition(double x, double y)
  {

    SDL_WarpMouseInWindow(window, 
      static_cast<int>((x - mouseOffsetX) / mouseScaleX),
      static_cast<int>((y - mouseOffsetY) / mouseScaleY));

    #if !defined(OPTIBITS_X)
      // On systems where we have a working GetGlobalMouseState
      updateMousePosition();
    #else
      mouseX = x, mouseY = y;
    #endif
  }
};

std::string Optibits::Input::idToChar(Key key)
{
  requireSdlVideo();

  if (key > KEY_RANGE_END)
    return "";

  if (key == KEY_SPACE) return " ";

  SDL_Keycode keycode = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(key));
  if (keycode == SDLK_UNKNOWN) return "";

  const char* name = SDL_GetKeyName(keycode);
  if (name == nullptr) return "";


  std::u32string codepoints = utf8ToComposedUtc4(name);

  if (codepoints.length() != 1) return "";

  codepoints[0] = utf8proc_tolower(codepoints[0]);

  utf8proc_uint8_t utf8Buffer[4];

  auto len = utf8proc_encode_char(codepoints[0], utf8Buffer);

  return string(reinterpret_cast<char*>(utf8Buffer),len);
}


#endif