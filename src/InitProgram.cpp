#include "InitProgram.h"

InitProgram::InitProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds)
    : Program(buttons, switchProgram, leds, true),
    showRainbow(true)
{ }

void InitProgram::ButtonPressed(ButtonId button)
{
    if (button == BLACK)
    {
        showRainbow = !showRainbow;
    }
    else
    {
        switchProgram(static_cast<Programs>(button));
    }
}

void InitProgram::Setup()
{
    showRainbow = true;
}

void InitProgram::Loop()
{
    EVERY_N_MILLISECONDS(100){
        index = (++index) % 8;
    }
    leds.Fade();
    if (showRainbow)
    {
        leds.FillRainbowBlack();
    }
    buttons[index + 1].Fill(buttons[index + 1].GetColor());
}
