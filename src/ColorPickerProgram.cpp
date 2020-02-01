#include "ColorPickerProgram.h"

ColorPickerProgram::ColorPickerProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds) :
    Program(buttons, switchProgram, leds),
    color(CRGB::White),
    rainbow(false)
{ }

void ColorPickerProgram::ButtonPressed(ButtonId button)
{
    if (AllButtonsOff())
    {
        color   = buttons[button].GetColor();
        rainbow = buttons[button].IsRainbow();
    }

    if (buttons[button].IsOn())
    {
        buttons[button].TurnOff();
    }
    else
    {
        buttons[button].TurnOn(color, rainbow);
    }
}

void ColorPickerProgram::Setup()
{
    color = true;
}

void ColorPickerProgram::Loop()
{ }
