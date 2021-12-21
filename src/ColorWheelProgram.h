#pragma once

#include "Button.h"
#include "Program.h"

class ColorWheelProgram : public Program
{
  public:
    ColorWheelProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds& leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

  private:
    ProgramSwitch switchProgram;
};
