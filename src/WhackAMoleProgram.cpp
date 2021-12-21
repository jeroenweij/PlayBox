#include "WhackAMoleProgram.h"
#include "Arduino.h"

WhackAMoleProgram::WhackAMoleProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds& leds, bool inverted) :
    Program(buttons, switchProgram, leds),
    level(0),
    inverted(inverted),
    finishAt(0)
{
}

void WhackAMoleProgram::ButtonPressed(ButtonId button)
{
    if (state == PRESS)
    {
        if (inverted != buttons[button].IsOn())
        {
            ++level;
            buttons[button].Turn(inverted);
        }
        else
        {
            EnterFailState(level);
        }

        if ((!inverted && AllButtonsOff()) || (inverted && AllButtonsOn()))
        {
            nextAction = millis() + 200 + random() % 400;
            state      = WAIT;
        }
    }
    else if (state == SCORE)
    {
        switchProgram(INIT);
    }
}

void WhackAMoleProgram::Setup()
{
    randomSeed(analogRead(A4) + millis());
    state = WAIT;
    level = 0;
    if (inverted)
    {
        for (auto& button : buttons)
        {
            button.TurnOn();
        }
    }
    finishAt = millis() + 30000;
}

void WhackAMoleProgram::Loop()
{
    static uint8_t count = 0;

    if (state == CHOOSE)
    {
        if (finishAt <= millis())
        {
            TurnButtonsOff();
            leds.Print(level, CRGB::Blue);
            state      = SCORE;
            nextAction = millis() + 5000;
            return;
        }
        count         = 0;
        uint8_t moles = random() % 3 + 1;
        for (uint8_t i = 0; i < moles; ++i)
        {
            buttons[random() % 9].Turn(!inverted);
        }
        state = PRESS;
    }
    else if (state == WAIT)
    {
        if (nextAction <= millis())
        {
            state = CHOOSE;
        }
    }
    else if (state == SCORE)
    {
        if (nextAction <= millis())
        {
            switchProgram(INIT);
        }
    }
}
