#pragma once

#include "Program.h"
#include "Button.h"

class WhackAMoleProgram : public Program
{
public:
    WhackAMoleProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds, bool inverted = false);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

private:
    enum MoleState
    {
        CHOOSE,
        PRESS,
        WAIT,
        SCORE
    };
    MoleState state;
    uint8_t level;
    bool inverted;
    unsigned long finishAt;
};
