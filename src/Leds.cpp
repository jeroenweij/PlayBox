#define FASTLED_ALLOW_INTERRUPTS      0
#define FASTLED_INTERRUPT_RETRY_COUNT 0

#include "Leds.h"

FASTLED_USING_NAMESPACE


#define NUM_LEDS          88
#define BRIGHTNESS        15 // 96
#define FRAMES_PER_SECOND 120

static CRGB leds[NUM_LEDS];

static CRGB* rings[9][12] = {
    // BLACK
    {&leds[0],  &leds[1],  &leds[2],  &leds[3],  &leds[4],  &leds[5],  &leds[6],  &leds[7],  &leds[8],  &leds[9],  &leds[10], &leds[11]},
    // GREEN
    {&leds[25], &leds[26], &leds[56], &leds[57], &leds[58], &leds[59], &leds[60], &leds[61], &leds[62], &leds[63], &leds[23], &leds[24]},
    // ORANGE
    {&leds[21], &leds[22], &leds[23], &leds[63], &leds[62], &leds[64], &leds[65], &leds[66], &leds[67], &leds[68], &leds[69], &leds[20]},
    // PINK
    {&leds[76], &leds[17], &leds[18], &leds[19], &leds[20], &leds[69], &leds[70], &leds[71], &leds[72], &leds[73], &leds[74], &leds[75]},
    // YELLOW
    {&leds[81], &leds[82], &leds[14], &leds[15], &leds[16], &leds[17], &leds[76], &leds[75], &leds[77], &leds[78], &leds[79], &leds[80]},
    // BLUE
    {&leds[86], &leds[87], &leds[37], &leds[36], &leds[35], &leds[12], &leds[13], &leds[14], &leds[82], &leds[83], &leds[84], &leds[85]},
    // RED
    {&leds[39], &leds[40], &leds[41], &leds[42], &leds[43], &leds[32], &leds[33], &leds[34], &leds[35], &leds[36], &leds[37], &leds[38]},
    // WHITE
    {&leds[44], &leds[45], &leds[46], &leds[47], &leds[48], &leds[49], &leds[50], &leds[29], &leds[30], &leds[31], &leds[32], &leds[43]},
    // PURPLE
    {&leds[50], &leds[49], &leds[51], &leds[52], &leds[53], &leds[54], &leds[55], &leds[56], &leds[26], &leds[27], &leds[28], &leds[29]}
};

static CRGB* segment1[7][3] = {
    {&leds[80], &leds[81], &leds[82]},
    {&leds[77], &leds[78], &leds[79]},
    {&leds[14], &leds[15], &leds[16]},
    {&leds[17], &leds[75], &leds[76]},
    {&leds[72], &leds[73], &leds[74]},
    {&leds[18], &leds[19], &leds[20]},
    {&leds[69], &leds[70], &leds[71]},
};

static CRGB* segment2[7][3] = {
    {&leds[43], &leds[44], &leds[45]},
    {&leds[30], &leds[31], &leds[32]},
    {&leds[46], &leds[47], &leds[48]},
    {&leds[49], &leds[50], &leds[29]},
    {&leds[26], &leds[27], &leds[28]},
    {&leds[51], &leds[52], &leds[53]},
    {&leds[54], &leds[55], &leds[56]}
};


void Leds::Setup()
{
    FillSolid(CRGB::Black);
    static WS2811Controller800Khz<14, RGB> c;

    FastLED.addLeds(&c, leds, NUM_LEDS);

    // set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
}

void Leds::Loop()
{
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

CRGB** Leds::GetRing(uint8_t ringNum)
{
    return rings[ringNum];
}

void Leds::FillSolid(CRGB color)
{
    fill_solid(leds, NUM_LEDS, color);
}

void Leds::FillRainbow()
{
    fill_rainbow(leds, NUM_LEDS, 0, 21);
}

void Leds::FillRainbowBlack()
{
    fill_rainbow(leds, 12, 0, 21);
}

void Leds::Count(uint8_t c)
{
    for (uint8_t i = 0; i < c; i++)
    {
        leds[i]     = CRGB::Gold;
        leds[i + 1] = CRGB::Black;
    }
}

void Leds::Print(uint8_t num, CRGB color)
{
    if (num > 99)
    {
        num = 99;
    }

    PrintDigit(segment1, num / 10, color);
    PrintDigit(segment2, num % 10, color);
}

void Leds::PrintDigit(CRGB* segment[7][3], uint8_t digit, CRGB color)
{
    static uint8_t nums[10] = {119, 36, 93, 109, 46, 107, 123, 37, 127, 111};

    for (uint8_t i = 0; i < 7; i++)
    {
        if (nums[digit] >> i & 0x01)
        {
            for (auto& l : segment[i])
            {
                *l = color;
            }
        }
        else
        {
            for (auto& l : segment[i])
            {
                *l = CRGB::Black;
            }
        }
    }
}

void Leds::Fade()
{
    fadeToBlackBy(leds, NUM_LEDS, 10);
}
