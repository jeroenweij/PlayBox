#include "MixUpProgram.h"

MixUpProgram::MixUpProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds) :
    Program(buttons, switchProgram, leds),
    colorId(0),
    prevButtonId(0),
    score(0),
    finishAt(0),
    showScore(false)
{ }

void MixUpProgram::ButtonPressed(ButtonId button)
{
    if (showScore)
    {
        switchProgram(INIT);
    }
    else
    {
        if (button == colorId)
        {
            ++score;
            if (finishAt <= millis())
            {
                TurnButtonsOff();
                leds.Print(score, CRGB::Blue);
                showScore  = true;
                nextAction = millis() + 5000;
            }
            else
            {
                buttons[prevButtonId].TurnOff();
                SelectButton(button);
            }
        }
        else
        {
            EnterFailState(score);
        }
    }
}

void MixUpProgram::Setup()
{
    score     = 0;
    showScore = false;
    SelectButton(random() % 9);
    finishAt = millis() + 15000;
}

void MixUpProgram::Loop()
{
    if (showScore && (nextAction <= millis()))
    {
        switchProgram(INIT);
    }
}

void MixUpProgram::SelectButton(uint8_t buttonId)
{
    colorId = random() % 9;

    buttons[buttonId].TurnOn(buttons[colorId].GetColor(), buttons[colorId].IsRainbow());
    prevButtonId = buttonId;
}
