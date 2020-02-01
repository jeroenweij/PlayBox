#pragma once

#include <FastLED.h>

class Leds
{
public:
    void Setup();
    void Loop();

    CRGB** GetRing(uint8_t ringNum);
    void FillSolid(CRGB color);
    void FillRainbow();
    void Fade();
    void FillRainbowBlack();

    void Print(uint8_t num, CRGB color);
private:
    void PrintDigit(CRGB* segment[7][3], uint8_t digit, CRGB color);
};
