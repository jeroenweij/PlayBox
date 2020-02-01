#pragma once

#include "Program.h"
#include "Button.h"

class MixUpProgram : public Program
{
public:
    MixUpProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

private:
    void SelectButton(uint8_t buttonId);

    uint8_t colorId;
    uint8_t prevButtonId;
    uint8_t score;
    unsigned long finishAt;
    bool showScore;
};
