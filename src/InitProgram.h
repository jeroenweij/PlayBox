#pragma once

#include "Program.h"
#include "Button.h"

class InitProgram : public Program
{
public:
    InitProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

private:
    uint8_t index = 0;
    bool showRainbow;
};
