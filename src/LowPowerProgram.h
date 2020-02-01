#pragma once

#include "Program.h"
#include "Button.h"

class LowPowerProgram : public Program
{
public:
    LowPowerProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

private:
    void sleepNow();
};
