#include "SimonProgram.h"
#include "Arduino.h"

SimonProgram::SimonProgram(Button (&buttons)[9], ProgramSwitch switchProgram, Leds &leds) :
    Program(buttons, switchProgram, leds),
    level(0),
    state(SimonState::MAKE),
    checkId(0),
    lastScore(0)
{ }

void SimonProgram::ButtonPressed(ButtonId button)
{
    if (state == SimonState::INPUTS)
    {
        TurnButtonsOff();
        if (sequence[checkId] != button)
        {
            lastScore = level;
            state     = SimonState::FAIL;
            EnterFailState(level);
        }
        else
        {
            buttons[button].TurnOn();
            ++checkId;
            if (checkId == level)
            {
                state      = SimonState::OK;
                nextAction = millis() + 800;
                leds.FillSolid(CRGB::Green);
            }
        }
    }
    else if (state == SimonState::SHOW)
    {
        if (level < 2)
        {
            state = SimonState::SCORE;
            TurnButtonsOff();
            leds.Print(lastScore, CRGB::Blue);
        }
    }
    else if (state == SimonState::OK)
    {
        state = SimonState::MAKE;
    }
    else if (state == SimonState::SCORE)
    {
        TurnButtonsOff();
        state = SimonState::SHOW;
    }
}

void SimonProgram::Setup()
{
    level   = 0;
    state   = SimonState::MAKE;
    checkId = 0;
    randomSeed(analogRead(A4) + millis());
}

static bool IsNeighbor(uint8_t a, uint8_t b)
{
    if (a == b)
    {
        return true;
    }
    if (a == 0 || b == 0)
    {
        return false;
    }
    return (max(a, b) - min(a, b) == 1);
}

void SimonProgram::Loop()
{
    static uint8_t step = 0;

    switch (state)
    {
        case SimonState::MAKE:
        {
            TurnButtonsOff();
            if (level == MAX_LEVEL)
            {
                switchProgram(INIT);
                return;
            }
            sequence[level] = random() % 9;
            while (level > 0 && IsNeighbor(sequence[level], sequence[level - 1]))
            {
                sequence[level] = random() % 9;
            }
            ++level;
            step       = 0;
            state      = SimonState::SHOW;
            nextAction = millis() + 800;
            break;
        }
        case SimonState::SHOW:
        {
            if (nextAction <= millis())
            {
                if (step > 0)
                {
                    buttons[sequence[step - 1]].TurnOff();
                }

                if (step < level)
                {
                    buttons[sequence[step]].TurnOn();
                    buttons[sequence[step]].PlayTone(200);

                    ++step;
                }
                else
                {
                    checkId = 0;
                    step    = 0;
                    state   = SimonState::INPUTS;
                }
                nextAction = millis() + (800 - 25 * level);
            }
            break;
        }
        case SimonState::OK:
        {
            if (nextAction <= millis())
            {
                state = SimonState::MAKE;
                step  = 0;
            }

            break;
        }
        case SimonState::SCORE:
        {
            step = 0;
            break;
        }
    }
}
