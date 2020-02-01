#include "ToggleProgram.h"

ToggleProgram::ToggleProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds) :
    Program(buttons, switchProgram, leds),
    goOn(true)
{ }

void ToggleProgram::ButtonPressed(ButtonId button)
{
    buttons[button].Toggle();

    if (goOn)
    {
        goOn = !AllButtonsOn();
    }
    else
    {
        goOn = AllButtonsOff();

        if (goOn)
        {
            switchProgram(INIT);
        }
    }
}

void ToggleProgram::Setup()
{
    goOn = true;
}

void ToggleProgram::Loop()
{ }
