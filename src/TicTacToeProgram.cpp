#include "TicTacToeProgram.h"

TicTacToeProgram::TicTacToeProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds& leds) :
    Program(buttons, switchProgram, leds),
    state(State::PLAY),
    player1(true)
{
}

void TicTacToeProgram::ButtonPressed(ButtonId button)
{
    if (state == State::PLAY)
    {
        if (!buttons[button].IsOn())
        {
            buttons[button].TurnOn(player1 ? CRGB::Red : CRGB::Green, false);
            player1 = !player1;
        }

        if (Is3InLine())
        {
            nextAction = millis() + 500;
            state      = State::SHOW;
        }
        else
        {
            if (AllButtonsOn())
            {
                nextAction = millis() + 1000;
                state      = State::FAIL;
            }
        }
    }
}

void TicTacToeProgram::Setup()
{
    state   = State::PLAY;
    player1 = true;
}

void TicTacToeProgram::Loop()
{
    static uint8_t c = 0;

    if (state == State::PLAY)
    {
        c = 8;
    }
    else if (state == State::SHOW)
    {
        if (nextAction <= millis())
        {
            if (player1)
            {
                for (const auto& i : winLine)
                {
                    buttons[i].TurnOn(winCollor, false);
                }
            }
            else
            {
                for (const auto& i : winLine)
                {
                    buttons[i].TurnOff();
                }
            }
            player1 = !player1;
            --c;
            nextAction = millis() + 500;
        }
        if (c == 0)
        {
            switchProgram(INIT);
        }
    }
    else if (state == State::FAIL)
    {
        if (nextAction <= millis())
        {
            switchProgram(INIT);
        }
    }
}

bool TicTacToeProgram::Is3InLine()
{
    if (buttons[0].IsOn())
    {
        CRGB color = buttons[0].GetColor();

        for (uint8_t i = 1; i <= 4; ++i)
        {
            if (buttons[i].IsOn() && (buttons[i].GetColor() == color) &&
                buttons[i + 4].IsOn() && (buttons[i + 4].GetColor() == color))
            {
                winLine[0] = 0;
                winLine[1] = i;
                winLine[2] = i + 4;
                winCollor  = color;
                return true;
            }
        }
    }

    for (uint8_t i = 0; i < 8; ++i)
    {
        if (buttons[i + 1].IsOn())
        {
            CRGB color = buttons[i + 1].GetColor();
            if (buttons[(i + 1) % 8 + 1].IsOn() && (buttons[(i + 1) % 8 + 1].GetColor() == color) &&
                buttons[(i + 2) % 8 + 1].IsOn() && (buttons[(i + 2) % 8 + 1].GetColor() == color))
            {
                winLine[0] = i + 1;
                winLine[1] = (i + 1) % 8 + 1;
                winLine[2] = (i + 2) % 8 + 1;
                winCollor  = color;
                return true;
            }
        }
    }
    return false;
}
