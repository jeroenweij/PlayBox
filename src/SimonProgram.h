#pragma once

#include "Program.h"
#include "Button.h"

#define MAX_LEVEL 15

class SimonProgram : public Program
{
public:
    SimonProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

private:
    enum class SimonState
    {
        MAKE,
        SHOW,
        SCORE,
        INPUTS,
        OK,
        FAIL
    };

    uint8_t sequence[MAX_LEVEL];
    uint8_t level;
    SimonState state;
    uint8_t checkId;
    uint8_t lastScore;
};
