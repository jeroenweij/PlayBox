#include "ColorWheelProgram.h"

ColorWheelProgram::ColorWheelProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds)
    : Program(buttons, switchProgram, leds)
{ }

void ColorWheelProgram::ButtonPressed(ButtonId button)
{
    if (button == BLACK)
    {
        leds.FillRainbow();
    }
    else
    {
        leds.FillSolid(buttons[button].GetColor());
    }
}

void ColorWheelProgram::Setup()
{ }

void ColorWheelProgram::Loop()
{ }
