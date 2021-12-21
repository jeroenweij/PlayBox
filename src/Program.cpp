#include "Program.h"
#include "InitProgram.h"

Program::~Program()
{
}

Program::Program(Button (&buttons)[9], ProgramSwitch switchProgram, Leds& leds, bool isInit) :
    buttons(buttons),
    switchProgram(switchProgram),
    leds(leds),
    blackCount(0),
    failState(false),
    timeout(0),
    isInit(isInit),
    nextAction(0),
    leaveFailState(0)
{
}

void Program::ButtonPressedCheckExit(ButtonId button)
{
    timeout = 0;
    if (button == BLACK)
    {
        blackCount++;

        if (failState || blackCount == 5)
        {
            if (isInit)
            {
                failState = false;
                leds.FillSolid(CRGB::White);
                switchProgram(LOWPOWER);
                return;
            }
            else
            {
                failState = false;
                switchProgram(INIT);
                return;
            }
            blackCount = 0;
        }
    }
    else
    {
        blackCount = 0;
    }

    if (failState)
    {
        if (leaveFailState <= millis())
        {
            failState = false;
            switchProgram(INIT);
            return;
        }
    }
    else
    {
        ButtonPressed(button);
    }
}

void Program::Teardown()
{
    for (auto& button : buttons)
    {
        button.TurnOff();
        blackCount = 0;
    }
    failState = false;
    timeout   = 0;
}

void Program::CheckTimeout()
{
    EVERY_N_SECONDS(1)
    {
        ++timeout;
        if (timeout == 90)
        {
            if (isInit)
            {
                switchProgram(LOWPOWER);
            }
            else
            {
                switchProgram(INIT);
            }
        }
    }

    if (failState)
    {
        if (nextAction <= millis())
        {
            switchProgram(INIT);
        }
    }
}

void Program::TurnButtonsOff()
{
    for (auto& button : buttons)
    {
        button.TurnOff();
    }
}

bool Program::AllButtonsOff()
{
    for (auto& button : buttons)
    {
        if (button.IsOn())
        {
            return false;
        }
    }
    return true;
}

bool Program::AllButtonsOn()
{
    for (auto& button : buttons)
    {
        if (!button.IsOn())
        {
            return false;
        }
    }
    return true;
}

void Program::EnterFailState(uint8_t score)
{
    failState = true;
    leds.FillSolid(CRGB::Red);
    if (score > 0)
    {
        leds.Print(score, CRGB::Blue);
    }
    nextAction     = millis() + (score > 0 ? 5000 : 1200);
    leaveFailState = millis() + 1000;
}
