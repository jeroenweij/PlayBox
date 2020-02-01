#include <FastLED.h>

#include <stdint.h>
#include "Arduino.h"
#include "Leds.h"
#include "Button.h"
#include "Program.h"
#include "InitProgram.h"
#include "ColorWheelProgram.h"
#include "SimonProgram.h"
#include "WhackAMoleProgram.h"
#include "ToggleProgram.h"
#include "MixUpProgram.h"
#include "LowPowerProgram.h"
#include "TicTacToeProgram.h"
#include "ColorPickerProgram.h"

void ButtonCalled(ButtonId button);
void SwitchProgram(Programs newProgram);

static Leds leds;
static Button buttons[9] = {
    Button(ButtonId::BLACK,  2,  CRGB::Gray,       leds.GetRing(0), &ButtonCalled,  true),
    Button(ButtonId::GREEN,  3,  CRGB::Green,      leds.GetRing(1), &ButtonCalled),
    Button(ButtonId::ORANGE, 4,  CRGB::OrangeRed,  leds.GetRing(2), &ButtonCalled),
    Button(ButtonId::PINK,   5,  CRGB::DeepPink,   leds.GetRing(3), &ButtonCalled),
    Button(ButtonId::YELLOW, 6,  CRGB::Yellow,     leds.GetRing(4), &ButtonCalled),
    Button(ButtonId::BLUE,   7,  CRGB::Blue,       leds.GetRing(5), &ButtonCalled),
    Button(ButtonId::RED,    8,  CRGB::Red,        leds.GetRing(6), &ButtonCalled),
    Button(ButtonId::WHITE,  9,  CRGB::WhiteSmoke, leds.GetRing(7), &ButtonCalled),
    Button(ButtonId::PURPLE, 10, CRGB::Purple,     leds.GetRing(8), &ButtonCalled)
};

static void setNeighbors()
{
    buttons[GREEN].SetNeighbor({&buttons[PURPLE], 1, 2});
    buttons[GREEN].SetNeighbor({&buttons[ORANGE], 8, 3});
    buttons[ORANGE].SetNeighbor({&buttons[GREEN], 2, 3});
    buttons[ORANGE].SetNeighbor({&buttons[PINK], 10, 2});
    buttons[PINK].SetNeighbor({&buttons[ORANGE], 4, 2});
    buttons[PINK].SetNeighbor({&buttons[YELLOW], 11, 3});
    buttons[YELLOW].SetNeighbor({&buttons[PINK], 5, 3});
    buttons[YELLOW].SetNeighbor({&buttons[BLUE], 1, 2});
    buttons[BLUE].SetNeighbor({&buttons[YELLOW], 7, 2});
    buttons[BLUE].SetNeighbor({&buttons[RED], 2, 3});
    buttons[RED].SetNeighbor({&buttons[BLUE], 8, 3});
    buttons[RED].SetNeighbor({&buttons[WHITE], 4, 2});
    buttons[WHITE].SetNeighbor({&buttons[RED], 10, 2});
    buttons[WHITE].SetNeighbor({&buttons[PURPLE], 5, 3});
    buttons[PURPLE].SetNeighbor({&buttons[WHITE], 11, 3});
    buttons[PURPLE].SetNeighbor({&buttons[GREEN], 7, 2});
}

static InitProgram initProgram(buttons, &SwitchProgram, leds);
static ColorWheelProgram colorWheelProgram(buttons, &SwitchProgram, leds);
static SimonProgram simonProgram(buttons, &SwitchProgram, leds);
static WhackAMoleProgram whackAMoleProgram(buttons, &SwitchProgram, leds);
static WhackAMoleProgram whackAMoleInvProgram(buttons, &SwitchProgram, leds, true);
static ToggleProgram toggleProgram(buttons, &SwitchProgram, leds);
static MixUpProgram mixUpProgram(buttons, &SwitchProgram, leds);
static TicTacToeProgram ticTacToeProgram(buttons, &SwitchProgram, leds);
static ColorPickerProgram colorPickerProgram(buttons, &SwitchProgram, leds);
static LowPowerProgram lowPowerProgram(buttons, &SwitchProgram, leds);

static Program* programList[10] = {&initProgram,
                                   &colorWheelProgram,
                                   &ticTacToeProgram,
                                   &whackAMoleProgram,
                                   &whackAMoleInvProgram,
                                   &toggleProgram,
                                   &mixUpProgram,
                                   &simonProgram,
                                   &colorPickerProgram,
                                   &lowPowerProgram};

static Program* currentProgram = &initProgram;

void ButtonCalled(ButtonId button)
{
    currentProgram->ButtonPressedCheckExit(button);
}

void SwitchProgram(Programs newProgram)
{
    currentProgram->Teardown();
    currentProgram = programList[newProgram];
    currentProgram->Setup();
}

int main(void)
{
    init();

    USBDevice.attach();

    for (auto& button : buttons)
    {
        button.Setup();
    }
    setNeighbors();

    SwitchProgram(Programs::INIT);
    pinMode(15, OUTPUT);
    digitalWrite(15, HIGH);
    leds.Setup();
    for (;;)
    {
        currentProgram->Loop();
        currentProgram->CheckTimeout();

        leds.Loop();

        for (auto& button : buttons)
        {
            button.Loop();
        }
        delay(1);
        if (serialEventRun){serialEventRun();}
    }
}
