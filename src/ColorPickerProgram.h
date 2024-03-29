#pragma once

#include "Button.h"
#include "Program.h"

class ColorPickerProgram : public Program
{
  public:
    ColorPickerProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds& leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

  private:
    CRGB color;
    bool rainbow;
};
