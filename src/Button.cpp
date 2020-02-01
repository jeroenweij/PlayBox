#include "Button.h"
#include "Arduino.h"

Button::Button(ButtonId id, uint8_t pin, CRGB color, CRGB* leds[12], ButtonCallback callback, bool rainbow) :
    id(id),
    pin(pin),
    color(color),
    currentColor(color),
    bouncecount(0),
    pressed(false),
    callback(callback),
    isRainbow(rainbow),
    currentRainbow(rainbow),
    neighbor1({nullptr, 0, 0}),
    neighbor2({nullptr, 0, 0})
{
    for (int i = 0; i < 12; ++i)
    {
        this->leds[i] = leds[i];
    }

    fill_solid(this->leds[0], 12, color);
}

void Button::Setup()
{
    pinMode(pin, INPUT_PULLUP);
}

void Button::Loop()
{
    if (digitalRead(pin) == LOW)
    {
        if (bouncecount < 5)
        {
            ++bouncecount;
        }
    }
    else
    {
        if (bouncecount > 0)
        {
            --bouncecount;
        }
    }

    if (pressed)
    {
        if (bouncecount < 3)
        {
            pressed = false;
        }
    }
    else
    {
        if (bouncecount > 3)
        {
            pressed = true;
            callback(id);
        }
    }
}

void Button::TurnOn(CRGB color, bool rainbow)
{
    currentColor   = color;
    currentRainbow = rainbow;
    if (rainbow)
    {
        Rainbow();
    }
    else
    {
        Fill(color);
        CheckNeighbor(neighbor2);
    }
    isOn = true;
}

void Button::Fill(CRGB color)
{
    for (const auto &led : leds)
    {
        if (led != NULL)
        {
            *led = color;
        }
    }
}

void Button::Turn(bool on)
{
    if (on)
    {
        TurnOn();
    }
    else
    {
        TurnOff();
    }
}

void Button::TurnOn()
{
    TurnOn(color, isRainbow);
}

void Button::TurnOff()
{
    Fill(CRGB::Black);
    if (currentRainbow)
    {
        CheckNeighborRainbow(neighbor1);
        CheckNeighborRainbow(neighbor2);
    }
    else
    {
        CheckNeighbor(neighbor1);
        CheckNeighbor(neighbor2);
    }
    isOn = false;
}

void Button::CheckNeighbor(Neighbor& neighbor)
{
    if (neighbor.button != nullptr)
    {
        if (neighbor.button->IsOn())
        {
            for (uint8_t i = 0; i < neighbor.num; ++i)
            {
                *leds[(neighbor.start + i) % 12] = neighbor.button->GetColor();
            }
        }
    }
}

void Button::CheckNeighborRainbow(Neighbor& neighbor)
{
    if (neighbor.button != nullptr)
    {
        if (neighbor.button->IsOn())
        {
            neighbor.button->TurnOn(color, true);
        }
    }
}

void Button::Toggle()
{
    if (isOn)
    {
        TurnOff();
    }
    else
    {
        TurnOn();
    }
}

bool Button::IsOn() const
{
    return isOn;
}

bool Button::IsRainbow() const
{
    return isRainbow;
}

CRGB Button::GetColor() const
{
    return isOn ? currentColor : color;
}

void Button::SetNeighbor(Neighbor neighbor)
{
    if (neighbor1.button == nullptr)
    {
        neighbor1 = neighbor;
    }
    else
    {
        neighbor2 = neighbor;
    }
}

void Button::Rainbow()
{
    isOn = true;

    CHSV hsv;
    hsv.hue = 0;
    hsv.val = 255;
    hsv.sat = 240;
    for (const auto &led : leds)
    {
        *led     = hsv;
        hsv.hue += 21;
    }
}
