#pragma once

#include "Button.h"
#include "Leds.h"

enum Programs
{
    INIT, // BLACK
    COLORWHEEL, // GREEN
    TICTACTOE, // ORANGE
    WHACKAMOLE, // PINK
    WHACKAMOLEINV, // YELLOW
    TOGGLE, // BLUE
    MIXUP, // RED
    SIMON, // WHITE
    COLORPICKER, // PURPLE
    LOWPOWER
};

typedef void (*ProgramSwitch)(Programs newProgram);

class Program
{
  public:
    virtual ~Program() = 0;
    Program(Button (&buttons)[9], ProgramSwitch switchProgram, Leds& leds, bool isInit = false);

    void         ButtonPressedCheckExit(ButtonId button);
    virtual void ButtonPressed(ButtonId button) = 0;

    virtual void Setup() = 0;
    virtual void Loop()  = 0;
    virtual void Teardown();

    void CheckTimeout();

  protected:
    void TurnButtonsOff();
    bool AllButtonsOff();
    bool AllButtonsOn();
    void EnterFailState(uint8_t score = 0);

    Button (&buttons)[9];
    ProgramSwitch switchProgram;
    Leds&         leds;
    unsigned long nextAction;

  private:
    uint8_t       blackCount;
    bool          failState;
    uint8_t       timeout;
    bool          isInit;
    unsigned long leaveFailState;
};
