#pragma once


namespace Optibits
{
  enum key
  {
    KEY_UNKNOWN,

    KEY_RETURN,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,
    KEY_EXCLAIM,
    KEY_QUOTEDBL,
    KEY_HASH,
    KEY_PERCENT,
    KEY_DOLLAR,
    KEY_AMPERSAND,
    KEY_QUOTE,
    KEY_LEFTPAREN,
    KEY_RIGHTPAREN,
    KEY_ASTERISK,
    KEY_PLUS,
    KEY_COMMA,
    KEY_MINUS,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_COLON,
    KEY_SEMICOLON,
    KEY_LESS,
    KEY_EQUALS,
    KEY_GREATER,
    KEY_QUESTION,
    KEY_AT,

    KEY_LEFTBRACKET,
    KEY_BACKSLASH,
    KEY_RIGHTBRACKET,
    KEY_CARET,
    KEY_UNDERSCORE,
    KEY_BACKQUOTE,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    KEY_CAPSLOCK,

    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    KEY_PRINTSCREEN,
    KEY_SCROLLLOCK,
    KEY_PAUSE,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGEUP,
    KEY_DELETE,
    KEY_END,
    KEY_PAGEDOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,

    KEY_NUMLOCKCLEAR,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_MINUS,
    KEY_KP_PLUS,
    KEY_KP_ENTER,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_0,
    KEY_KP_PERIOD,
    KEY_KP_COMMA,
    KEY_KP_EQUALS,

    KEY_APPLICATION,
    KEY_POWER,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_EXECUTE,
    KEY_HELP,
    KEY_MENU,
    KEY_SELECT,
    KEY_STOP,
    KEY_AGAIN,
    KEY_UNDO,
    KEY_CUT,
    KEY_COPY,
    KEY_PASTE,
    KEY_FIND,
    KEY_MUTE,
    KEY_VOLUMEUP,
    KEY_VOLUMEDOWN,

    KEY_ALTERASE,
    KEY_SYSREQ,
    KEY_CANCEL,
    KEY_CLEAR,
    KEY_PRIOR,
    KEY_RETURN2,
    KEY_SEPARATOR,
    KEY_OUT,
    KEY_OPER,
    KEY_CLEARAGAIN,

    KEY_THOUSANDSSEPARATOR,
    KEY_DECIMALSEPARATOR,
    KEY_CURRENCYUNIT,
    KEY_CURRENCYSUBUNIT,

    KEY_LCTRL,
    KEY_LSHIFT,
    KEY_LALT,
    KEY_LGUI,
    KEY_RCTRL,
    KEY_RSHIFT,
    KEY_RALT,
    KEY_RGUI,

    KEY_MODE,

    KEY_AUDIONEXT,
    KEY_AUDIOPREV,
    KEY_AUDIOSTOP,
    KEY_AUDIOPLAY,
    KEY_AUDIOMUTE,
    KEY_MEDIASELECT,
    KEY_WWW,
    KEY_MAIL,
    KEY_CALCULATOR,
    KEY_COMPUTER,
    KEY_APP_SEARCH,
    KEY_APP_HOME,
    KEY_APP_BACK,
    KEY_APP_FORWARD,
    KEY_APP_STOP,
    KEY_APP_REFRESH,
    KEY_APP_BOOKMARKS,

    KEY_BRIGHTNESSDOWN,
    KEY_BRIGHTNESSUP,
    KEY_DISPLAYSWITCH,
    KEY_KBDILLUMTOGGLE,
    KEY_KBDILLUMDOWN,
    KEY_KBDILLUMUP,
    KEY_EJECT,
    KEY_SLEEP,

    KEY_MAX_ENUM

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
    NO_BUTTON,
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