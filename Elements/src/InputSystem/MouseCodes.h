/* Enum class for Mouse input codes and macros defined for them. */

#pragma once
namespace Elements {
enum class MouseCode {
  // From glfw3.h
  Button0 = 0,
  Button1 = 1,
  Button2 = 2,
  Button3 = 3,
  Button4 = 4,
  Button5 = 5,
  Button6 = 6,
  Button7 = 7,

  ButtonLast = Button7,
  ButtonLeft = Button0,
  ButtonRight = Button1,
  ButtonMiddle = Button2
};
}  // namespace Elements

#define ELMT_MOUSE_BUTTon_0 ::Elements::Mouse::Button0
#define ELMT_MOUSE_BUTTon_1 ::Elements::Mouse::Button1
#define ELMT_MOUSE_BUTTon_2 ::Elements::Mouse::Button2
#define ELMT_MOUSE_BUTTon_3 ::Elements::Mouse::Button3
#define ELMT_MOUSE_BUTTon_4 ::Elements::Mouse::Button4
#define ELMT_MOUSE_BUTTon_5 ::Elements::Mouse::Button5
#define ELMT_MOUSE_BUTTon_6 ::Elements::Mouse::Button6
#define ELMT_MOUSE_BUTTon_7 ::Elements::Mouse::Button7
#define ELMT_MOUSE_BUTTon_LAST ::Elements::Mouse::ButtonLast
#define ELMT_MOUSE_BUTTon_LEFT ::Elements::Mouse::ButtonLeft
#define ELMT_MOUSE_BUTTon_RIGHT ::Elements::Mouse::ButtonRight
#define ELMT_MOUSE_BUTTon_MIDDLE ::Elements::Mouse::ButtonMiddle
