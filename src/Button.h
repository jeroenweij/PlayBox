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

typedef void (*ButtonCallback)(ButtonId buttonId);

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
    Button(ButtonId id, uint8_t pin, CRGB color, uint16_t tone, CRGB* leds[], ButtonCallback callback, bool rainbow = false);

    void Setup();
    void PowerDown();
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
    void PlayTone(uint8_t len = 100);

  private:
    void Rainbow();

    void CheckNeighbor(Neighbor& neighbor);
    void CheckNeighborRainbow(Neighbor& neighbor);

    ButtonId   id;
    uint8_t    pin;
    const CRGB color;
    uint16_t   tone;
    CRGB       currentColor;
    CRGB*      leds[12];

    unsigned long  lastUpdate;
    bool           pressed;
    bool           isOn;
    ButtonCallback callback;
    bool           isRainbow;
    bool           currentRainbow;
    Neighbor       neighbor1;
    Neighbor       neighbor2;
};

#endif // BUTTON_H
