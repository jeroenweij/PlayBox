#pragma once

#include "Leds.h"

class SegmentDisplay
{
public:
    SegmentDisplay(Leds &leds);
private:

    struct Segment
    {
        CRGB* leds[3];
    };

    struct Digit
    {
        Segment segments[7];
    };
    Leds &leds;

    Digit digits[2];
};
