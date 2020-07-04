/* Enum class for Keyboard input codes and macros defined for them. */

#pragma once

namespace Elements {
enum class KeyCode {
    // From glfw3.h
    Space = 32,
    Apostrophe = 39, /* ' */
    Comma = 44,      /* , */
    Minus = 45,      /* - */
    Period = 46,     /* . */
    Slash = 47,      /* / */

    D0 = 48, /* 0 */
    D1 = 49, /* 1 */
    D2 = 50, /* 2 */
    D3 = 51, /* 3 */
    D4 = 52, /* 4 */
    D5 = 53, /* 5 */
    D6 = 54, /* 6 */
    D7 = 55, /* 7 */
    D8 = 56, /* 8 */
    D9 = 57, /* 9 */

    Semicolon = 59, /* ; */
    Equal = 61,     /* = */

    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    LeftBracket = 91,  /* [ */
    Backslash = 92,    /* \ */
    RightBracket = 93, /* ] */
    GraveAccent = 96,  /* ` */

    World1 = 161, /* non-US #1 */
    World2 = 162, /* non-US #2 */

    /* Function keys */
    Escape = 256,
    Enter = 257,
    Tab = 258,
    Backspace = 259,
    Insert = 260,
    Delete = 261,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    PageUp = 266,
    PageDown = 267,
    Home = 268,
    End = 269,
    CapsLock = 280,
    ScrollLock = 281,
    NumLock = 282,
    PrintScreen = 283,
    Pause = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,
    F25 = 314,

    /* Keypad */
    KP0 = 320,
    KP1 = 321,
    KP2 = 322,
    KP3 = 323,
    KP4 = 324,
    KP5 = 325,
    KP6 = 326,
    KP7 = 327,
    KP8 = 328,
    KP9 = 329,
    KPDecimal = 330,
    KPDivide = 331,
    KPMultiply = 332,
    KPSubtract = 333,
    KPAdd = 334,
    KPEnter = 335,
    KPEqual = 336,

    LeftShift = 340,
    LeftControl = 341,
    LeftAlt = 342,
    LeftSuper = 343,
    RightShift = 344,
    RightControl = 345,
    RightAlt = 346,
    RightSuper = 347,
    Menu = 348
};

}

// From glfw3.h
#define ELMT_KEY_SPACE         ::Elements::Key::Space
#define ELMT_KEY_APOSTROPHE    ::Elements::Key::Apostrophe /* ' */
#define ELMT_KEY_COMMA         ::Elements::Key::Comma      /* , */
#define ELMT_KEY_MINUS         ::Elements::Key::Minus      /* - */
#define ELMT_KEY_PERIOD        ::Elements::Key::Period     /* . */
#define ELMT_KEY_SLASH         ::Elements::Key::Slash      /* / */
#define ELMT_KEY_0             ::Elements::Key::D0
#define ELMT_KEY_1             ::Elements::Key::D1
#define ELMT_KEY_2             ::Elements::Key::D2
#define ELMT_KEY_3             ::Elements::Key::D3
#define ELMT_KEY_4             ::Elements::Key::D4
#define ELMT_KEY_5             ::Elements::Key::D5
#define ELMT_KEY_6             ::Elements::Key::D6
#define ELMT_KEY_7             ::Elements::Key::D7
#define ELMT_KEY_8             ::Elements::Key::D8
#define ELMT_KEY_9             ::Elements::Key::D9
#define ELMT_KEY_SEMICOLon     ::Elements::Key::Semicolon /* ; */
#define ELMT_KEY_EQUAL         ::Elements::Key::Equal     /* = */
#define ELMT_KEY_A             ::Elements::Key::A
#define ELMT_KEY_B             ::Elements::Key::B
#define ELMT_KEY_C             ::Elements::Key::C
#define ELMT_KEY_D             ::Elements::Key::D
#define ELMT_KEY_E             ::Elements::Key::E
#define ELMT_KEY_F             ::Elements::Key::F
#define ELMT_KEY_G             ::Elements::Key::G
#define ELMT_KEY_H             ::Elements::Key::H
#define ELMT_KEY_I             ::Elements::Key::I
#define ELMT_KEY_J             ::Elements::Key::J
#define ELMT_KEY_K             ::Elements::Key::K
#define ELMT_KEY_L             ::Elements::Key::L
#define ELMT_KEY_M             ::Elements::Key::M
#define ELMT_KEY_N             ::Elements::Key::N
#define ELMT_KEY_O             ::Elements::Key::O
#define ELMT_KEY_P             ::Elements::Key::P
#define ELMT_KEY_Q             ::Elements::Key::Q
#define ELMT_KEY_R             ::Elements::Key::R
#define ELMT_KEY_S             ::Elements::Key::S
#define ELMT_KEY_T             ::Elements::Key::T
#define ELMT_KEY_U             ::Elements::Key::U
#define ELMT_KEY_V             ::Elements::Key::V
#define ELMT_KEY_W             ::Elements::Key::W
#define ELMT_KEY_X             ::Elements::Key::X
#define ELMT_KEY_Y             ::Elements::Key::Y
#define ELMT_KEY_Z             ::Elements::Key::Z
#define ELMT_KEY_LEFT_BRACKET  ::Elements::Key::LeftBracket  /* [ */
#define ELMT_KEY_BACKSLASH     ::Elements::Key::Backslash    /* \ */
#define ELMT_KEY_RIGHT_BRACKET ::Elements::Key::RightBracket /* ] */
#define ELMT_KEY_GRAVE_ACCENT  ::Elements::Key::GraveAccent  /* ` */
#define ELMT_KEY_WORLD_1       ::Elements::Key::World1       /* non-US #1 */
#define ELMT_KEY_WORLD_2       ::Elements::Key::World2       /* non-US #2 */

/* Function keys */
#define ELMT_KEY_ESCAPE       ::Elements::Key::Escape
#define ELMT_KEY_ENTER        ::Elements::Key::Enter
#define ELMT_KEY_TAB          ::Elements::Key::Tab
#define ELMT_KEY_BACKSPACE    ::Elements::Key::Backspace
#define ELMT_KEY_INSERT       ::Elements::Key::Insert
#define ELMT_KEY_DELETE       ::Elements::Key::Delete
#define ELMT_KEY_RIGHT        ::Elements::Key::Right
#define ELMT_KEY_LEFT         ::Elements::Key::Left
#define ELMT_KEY_DOWN         ::Elements::Key::Down
#define ELMT_KEY_UP           ::Elements::Key::Up
#define ELMT_KEY_PAGE_UP      ::Elements::Key::PageUp
#define ELMT_KEY_PAGE_DOWN    ::Elements::Key::PageDown
#define ELMT_KEY_HOME         ::Elements::Key::Home
#define ELMT_KEY_END          ::Elements::Key::End
#define ELMT_KEY_CAPS_LOCK    ::Elements::Key::CapsLock
#define ELMT_KEY_SCROLL_LOCK  ::Elements::Key::ScrollLock
#define ELMT_KEY_NUM_LOCK     ::Elements::Key::NumLock
#define ELMT_KEY_PRINT_SCREEN ::Elements::Key::PrintScreen
#define ELMT_KEY_PAUSE        ::Elements::Key::Pause
#define ELMT_KEY_F1           ::Elements::Key::F1
#define ELMT_KEY_F2           ::Elements::Key::F2
#define ELMT_KEY_F3           ::Elements::Key::F3
#define ELMT_KEY_F4           ::Elements::Key::F4
#define ELMT_KEY_F5           ::Elements::Key::F5
#define ELMT_KEY_F6           ::Elements::Key::F6
#define ELMT_KEY_F7           ::Elements::Key::F7
#define ELMT_KEY_F8           ::Elements::Key::F8
#define ELMT_KEY_F9           ::Elements::Key::F9
#define ELMT_KEY_F10          ::Elements::Key::F10
#define ELMT_KEY_F11          ::Elements::Key::F11
#define ELMT_KEY_F12          ::Elements::Key::F12
#define ELMT_KEY_F13          ::Elements::Key::F13
#define ELMT_KEY_F14          ::Elements::Key::F14
#define ELMT_KEY_F15          ::Elements::Key::F15
#define ELMT_KEY_F16          ::Elements::Key::F16
#define ELMT_KEY_F17          ::Elements::Key::F17
#define ELMT_KEY_F18          ::Elements::Key::F18
#define ELMT_KEY_F19          ::Elements::Key::F19
#define ELMT_KEY_F20          ::Elements::Key::F20
#define ELMT_KEY_F21          ::Elements::Key::F21
#define ELMT_KEY_F22          ::Elements::Key::F22
#define ELMT_KEY_F23          ::Elements::Key::F23
#define ELMT_KEY_F24          ::Elements::Key::F24
#define ELMT_KEY_F25          ::Elements::Key::F25

/* Keypad */
#define ELMT_KEY_KP_0        ::Elements::Key::KP0
#define ELMT_KEY_KP_1        ::Elements::Key::KP1
#define ELMT_KEY_KP_2        ::Elements::Key::KP2
#define ELMT_KEY_KP_3        ::Elements::Key::KP3
#define ELMT_KEY_KP_4        ::Elements::Key::KP4
#define ELMT_KEY_KP_5        ::Elements::Key::KP5
#define ELMT_KEY_KP_6        ::Elements::Key::KP6
#define ELMT_KEY_KP_7        ::Elements::Key::KP7
#define ELMT_KEY_KP_8        ::Elements::Key::KP8
#define ELMT_KEY_KP_9        ::Elements::Key::KP9
#define ELMT_KEY_KP_DECIMAL  ::Elements::Key::KPDecimal
#define ELMT_KEY_KP_DIVIDE   ::Elements::Key::KPDivide
#define ELMT_KEY_KP_MULTIPLY ::Elements::Key::KPMultiply
#define ELMT_KEY_KP_SUBTRACT ::Elements::Key::KPSubtract
#define ELMT_KEY_KP_ADD      ::Elements::Key::KPAdd
#define ELMT_KEY_KP_ENTER    ::Elements::Key::KPEnter
#define ELMT_KEY_KP_EQUAL    ::Elements::Key::KPEqual

#define ELMT_KEY_LEFT_SHIFT    ::Elements::Key::LeftShift
#define ELMT_KEY_LEFT_ConTROL  ::Elements::Key::LeftControl
#define ELMT_KEY_LEFT_ALT      ::Elements::Key::LeftAlt
#define ELMT_KEY_LEFT_SUPER    ::Elements::Key::LeftSuper
#define ELMT_KEY_RIGHT_SHIFT   ::Elements::Key::RightShift
#define ELMT_KEY_RIGHT_ConTROL ::Elements::Key::RightControl
#define ELMT_KEY_RIGHT_ALT     ::Elements::Key::RightAlt
#define ELMT_KEY_RIGHT_SUPER   ::Elements::Key::RightSuper
#define ELMT_KEY_MENU          ::Elements::Key::Menu