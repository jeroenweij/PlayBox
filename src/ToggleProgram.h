#pragma once

#include "Program.h"
#include "Button.h"

class ToggleProgram : public Program
{
public:
    ToggleProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

private:
    bool goOn;
};
