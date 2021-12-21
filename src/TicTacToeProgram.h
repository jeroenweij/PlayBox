#pragma once

#include "Button.h"
#include "Program.h"

class TicTacToeProgram : public Program
{
  public:
    TicTacToeProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds& leds);
    void ButtonPressed(ButtonId button) override;

    void Setup() override;
    void Loop() override;

  private:
    enum class State
    {
        PLAY,
        SHOW,
        FAIL
    };

    State   state;
    bool    Is3InLine();
    bool    player1;
    uint8_t winLine[3];
    CRGB    winCollor;
};
