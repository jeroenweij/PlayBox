#ifndef BUTTON_H
#define BUTTON_H

#include <FastLED.h>

enum ButtonId
{
    BLACK,
    GREEN,
    ORANGE,
    PINK,
    YELLOW,
    BLUE,
    RED,
    WHITE,
    PURPLE
};

typedef void (* ButtonCallback)(ButtonId buttonId);

class Button;
struct Neighbor
{
    Button* button;
    uint8_t start;
    uint8_t num;
};

class Button
{
public:
    Button(ButtonId id, uint8_t pin, CRGB color, CRGB* leds[], ButtonCallback callback, bool rainbow = false);

    void Setup();
    void Loop();

    void TurnOn(CRGB color, bool rainbow);
    void Fill(CRGB color);
    void Turn(bool on);
    void TurnOn();
    void TurnOff();
    void Toggle();
    bool IsOn() const;
    bool IsRainbow() const;
    CRGB GetColor() const;
    void SetNeighbor(Neighbor neighbor);

private:
    void Rainbow();

    void CheckNeighbor(Neighbor& neighbor);
    void CheckNeighborRainbow(Neighbor& neighbor);

    ButtonId id;
    uint8_t pin;
    const CRGB color;
    CRGB currentColor;
    CRGB* leds[12];

    uint8_t bouncecount;
    bool pressed;
    bool isOn;
    ButtonCallback callback;
    bool isRainbow;
    bool currentRainbow;
    Neighbor neighbor1;
    Neighbor neighbor2;
};

#endif // BUTTON_H