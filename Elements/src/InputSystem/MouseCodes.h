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

#define ELMT_MOUSE_BUTTON_0 ::Elements::Mouse::Button0
#define ELMT_MOUSE_BUTTON_1 ::Elements::Mouse::Button1
#define ELMT_MOUSE_BUTTON_2 ::Elements::Mouse::Button2
#define ELMT_MOUSE_BUTTON_3 ::Elements::Mouse::Button3
#define ELMT_MOUSE_BUTTON_4 ::Elements::Mouse::Button4
#define ELMT_MOUSE_BUTTON_5 ::Elements::Mouse::Button5
#define ELMT_MOUSE_BUTTON_6 ::Elements::Mouse::Button6
#define ELMT_MOUSE_BUTTON_7 ::Elements::Mouse::Button7
#define ELMT_MOUSE_BUTTON_LAST ::Elements::Mouse::ButtonLast
#define ELMT_MOUSE_BUTTON_LEFT ::Elements::Mouse::ButtonLeft
#define ELMT_MOUSE_BUTTON_RIGHT ::Elements::Mouse::ButtonRight
#define ELMT_MOUSE_BUTTON_MIDDLE ::Elements::Mouse::ButtonMiddle