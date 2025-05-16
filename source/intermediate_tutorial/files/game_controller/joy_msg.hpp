#ifndef _JOY_MSG_HPP
#define _JOY_MSG_HPP

#include <stdint.h>

#define BUTTONS(button) (1 << button)

namespace myPS4
{
  enum Buttons
  {
    CROSS,
    CIRCLE,
    SQUARE,
    TRIANGLE,
    SHARE,
    PS_BUTTON,
    OPTION,
    L3,
    R3,
    L1,
    R1,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    TOUCH
  };
}

namespace myXBox
{
  enum Buttons
  {
    A,
    B,
    X,
    Y,
    BACK,
    XBOX_BUTTON,
    START,
    LSTICK,
    RSTICK,
    LB,
    RB,
    UP,
    DOWN,
    LEFT,
    RIGHT
  };
}

#pragma pack(push, 1)
struct JoyData
{
  int8_t lx;
  int8_t ly;
  int8_t rx;
  int8_t ry;
  uint8_t lt;
  uint8_t rt;
  uint16_t buttons;
};
#pragma pack(pop)

#endif // _JOY_MSG_HPP