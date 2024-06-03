#pragma once


namespace Optibits
{
  enum Key
  {
    // @amine : See SDL_Scancode -> https://wiki.libsdl.org/SDL2/SDL_Scancode
    KEY_ESCAPE = 41,
    KEY_F1 = 58,
    KEY_F2 = 59,
    KEY_F3 = 60,
    KEY_F4 = 61,
    KEY_F5 = 62,
    KEY_F6 = 63,
    KEY_F7 = 64,
    KEY_F8 = 65,
    KEY_F9 = 66,
    KEY_F10 = 67,
    KEY_F11 = 68,
    KEY_F12 = 69,
    KEY_0 = 39,
    KEY_1 = 30,
    KEY_2 = 31,
    KEY_3 = 32,
    KEY_4 = 33,
    KEY_5 = 34,
    KEY_6 = 35,
    KEY_7 = 36,
    KEY_8 = 37,
    KEY_9 = 38,
    KEY_TAB = 43,
    KEY_RETURN = 40,
    KEY_SPACE = 44,
    KEY_LEFT_SHIFT = 225,
    KEY_RIGHT_SHIFT = 229,
    KEY_LEFT_CONTROL = 224,
    KEY_RIGHT_CONTROL = 228,
    KEY_LEFT_ALT = 226,
    KEY_RIGHT_ALT = 230,
    KEY_LEFT_META = 227,
    KEY_RIGHT_META = 231,
    KEY_BACKSPACE = 42,
    KEY_LEFT = 80,
    KEY_RIGHT = 79,
    KEY_UP = 82,
    KEY_DOWN = 81,
    KEY_HOME = 74,
    KEY_END = 77,
    KEY_PRINT_SCREEN = 70,
    KEY_SCROLL_LOCK = 71,
    KEY_PAUSE = 72,
    KEY_INSERT = 73,
    KEY_DELETE = 76,
    KEY_PAGE_UP = 75,
    KEY_PAGE_DOWN = 78,
    KEY_ENTER = 88,
    KEY_BACKTICK = 53,
    KEY_MINUS = 45,
    KEY_EQUALS = 46,
    KEY_LEFT_BRACKET = 47,
    KEY_RIGHT_BRACKET = 48,
    KEY_BACKSLASH = 49,
    KEY_SEMICOLON = 51,
    KEY_APOSTROPHE = 52,
    KEY_COMMA = 54,
    KEY_PERIOD = 55,
    KEY_SLASH = 56,
    KEY_CAPS_LOCK = 57,
    KEY_A = 4,
    KEY_B = 5,
    KEY_C = 6,
    KEY_D = 7,
    KEY_E = 8,
    KEY_F = 9,
    KEY_G = 10,
    KEY_H = 11,
    KEY_I = 12,
    KEY_J = 13,
    KEY_K = 14,
    KEY_L = 15,
    KEY_M = 16,
    KEY_N = 17,
    KEY_O = 18,
    KEY_P = 19,
    KEY_Q = 20,
    KEY_R = 21,
    KEY_S = 22,
    KEY_T = 23,
    KEY_U = 24,
    KEY_V = 25,
    KEY_W = 26,
    KEY_X = 27,
    KEY_Y = 28,
    KEY_Z = 29,

    /// ` on US/UK macOS, < on EU macOS, \ on US/UK Windows
    KEY_ISO = 100,
    KEY_NUMPAD_0 = 98,
    KEY_NUMPAD_1 = 89,
    KEY_NUMPAD_2 = 90,
    KEY_NUMPAD_3 = 91,
    KEY_NUMPAD_4 = 92,
    KEY_NUMPAD_5 = 93,
    KEY_NUMPAD_6 = 94,
    KEY_NUMPAD_7 = 95,
    KEY_NUMPAD_8 = 96,
    KEY_NUMPAD_9 = 97,
    KEY_NUMPAD_DELETE = 99,
    KEY_NUMPAD_PLUS = 87,
    KEY_NUMPAD_MINUS = 86,
    KEY_NUMPAD_MULTIPLY = 85,
    KEY_NUMPAD_DIVIDE = 84,
    KEY_RANGE_END = 0xff,

    MS_RANGE_BEGIN,
    MS_LEFT = MS_RANGE_BEGIN,
    MS_MIDDLE,
    MS_RIGHT,
    MS_WHEEL_UP,
    MS_WHEEL_DOWN,
    MS_OTHER_0,
    MS_OTHER_1,
    MS_OTHER_2,
    MS_OTHER_3,
    MS_OTHER_4,
    MS_OTHER_5,
    MS_OTHER_6,
    MS_OTHER_7,

    GP_RANGE_BEGIN,
    GP_DPAD_LEFT = GP_RANGE_BEGIN,
    GP_DPAD_RIGHT,
    GP_DPAD_UP,
    GP_DPAD_DOWN,
    GP_BUTTON_0,
    GP_BUTTON_1,
    GP_BUTTON_2,
    GP_BUTTON_3,
    GP_BUTTON_4,
    GP_BUTTON_5,
    GP_BUTTON_6,
    GP_BUTTON_7,
    GP_BUTTON_8,
    GP_BUTTON_9,
    GP_BUTTON_10,
    GP_BUTTON_11,
    GP_BUTTON_12,
    GP_BUTTON_13,
    GP_BUTTON_14,
    GP_BUTTON_15,

    GP_0_DPAD_LEFT,
    GP_0_DPAD_RIGHT,
    GP_0_DPAD_UP,
    GP_0_DPAD_DOWN,
    GP_0_BUTTON_0,
    GP_0_BUTTON_1,
    GP_0_BUTTON_2,
    GP_0_BUTTON_3,
    GP_0_BUTTON_4,
    GP_0_BUTTON_5,
    GP_0_BUTTON_6,
    GP_0_BUTTON_7,
    GP_0_BUTTON_8,
    GP_0_BUTTON_9,
    GP_0_BUTTON_10,
    GP_0_BUTTON_11,
    GP_0_BUTTON_12,
    GP_0_BUTTON_13,
    GP_0_BUTTON_14,
    GP_0_BUTTON_15,

    GP_1_DPAD_LEFT,
    GP_1_DPAD_RIGHT,
    GP_1_DPAD_UP,
    GP_1_DPAD_DOWN,
    GP_1_BUTTON_0,
    GP_1_BUTTON_1,
    GP_1_BUTTON_2,
    GP_1_BUTTON_3,
    GP_1_BUTTON_4,
    GP_1_BUTTON_5,
    GP_1_BUTTON_6,
    GP_1_BUTTON_7,
    GP_1_BUTTON_8,
    GP_1_BUTTON_9,
    GP_1_BUTTON_10,
    GP_1_BUTTON_11,
    GP_1_BUTTON_12,
    GP_1_BUTTON_13,
    GP_1_BUTTON_14,
    GP_1_BUTTON_15,

    GP_2_DPAD_LEFT,
    GP_2_DPAD_RIGHT,
    GP_2_DPAD_UP,
    GP_2_DPAD_DOWN,
    GP_2_BUTTON_0,
    GP_2_BUTTON_1,
    GP_2_BUTTON_2,
    GP_2_BUTTON_3,
    GP_2_BUTTON_4,
    GP_2_BUTTON_5,
    GP_2_BUTTON_6,
    GP_2_BUTTON_7,
    GP_2_BUTTON_8,
    GP_2_BUTTON_9,
    GP_2_BUTTON_10,
    GP_2_BUTTON_11,
    GP_2_BUTTON_12,
    GP_2_BUTTON_13,
    GP_2_BUTTON_14,
    GP_2_BUTTON_15,

    GP_3_DPAD_LEFT,
    GP_3_DPAD_RIGHT,
    GP_3_DPAD_UP,
    GP_3_DPAD_DOWN,
    GP_3_BUTTON_0,
    GP_3_BUTTON_1,
    GP_3_BUTTON_2,
    GP_3_BUTTON_3,
    GP_3_BUTTON_4,
    GP_3_BUTTON_5,
    GP_3_BUTTON_6,
    GP_3_BUTTON_7,
    GP_3_BUTTON_8,
    GP_3_BUTTON_9,
    GP_3_BUTTON_10,
    GP_3_BUTTON_11,
    GP_3_BUTTON_12,
    GP_3_BUTTON_13,
    GP_3_BUTTON_14,
    GP_3_BUTTON_15,

    GP_LEFT,
    GP_RIGHT,
    GP_UP,
    GP_DOWN,

    GP_0_LEFT,
    GP_0_RIGHT,
    GP_0_UP,
    GP_0_DOWN,

    GP_1_LEFT,
    GP_1_RIGHT,
    GP_1_UP,
    GP_1_DOWN,

    GP_2_LEFT,
    GP_2_RIGHT,
    GP_2_UP,
    GP_2_DOWN,

    GP_3_LEFT,
    GP_3_RIGHT,
    GP_3_UP,
    GP_3_DOWN,
    GP_RANGE_END = GP_3_DOWN,

    NUM_GAMEPADS = 4,
    NO_BUTTON = 0xffffffff
  };

  enum Axis
  {
    GP_LEFT_STICK_X_AXIS,
    GP_LEFT_STICK_Y_AXIS,
    GP_RIGHT_STICK_X_AXIS,
    GP_RIGHT_STICK_Y_AXIS,
    GP_LEFT_TRIGGER_AXIS,
    GP_RIGHT_TRIGGER_AXIS,

    GP_0_LEFT_STICK_X_AXIS,
    GP_0_LEFT_STICK_Y_AXIS,
    GP_0_RIGHT_STICK_X_AXIS,
    GP_0_RIGHT_STICK_Y_AXIS,
    GP_0_LEFT_TRIGGER_AXIS,
    GP_0_RIGHT_TRIGGER_AXIS,

    GP_1_LEFT_STICK_X_AXIS,
    GP_1_LEFT_STICK_Y_AXIS,
    GP_1_RIGHT_STICK_X_AXIS,
    GP_1_RIGHT_STICK_Y_AXIS,
    GP_1_LEFT_TRIGGER_AXIS,
    GP_1_RIGHT_TRIGGER_AXIS,

    GP_2_LEFT_STICK_X_AXIS,
    GP_2_LEFT_STICK_Y_AXIS,
    GP_2_RIGHT_STICK_X_AXIS,
    GP_2_RIGHT_STICK_Y_AXIS,
    GP_2_LEFT_TRIGGER_AXIS,
    GP_2_RIGHT_TRIGGER_AXIS,

    GP_3_LEFT_STICK_X_AXIS,
    GP_3_LEFT_STICK_Y_AXIS,
    GP_3_RIGHT_STICK_X_AXIS,
    GP_3_RIGHT_STICK_Y_AXIS,
    GP_3_LEFT_TRIGGER_AXIS,
    GP_3_RIGHT_TRIGGER_AXIS,

    NUM_AXES
  };
}