#include "Buzzer.h"
#include "Arduino.h"

/*************************************************
* Public Constants
*************************************************/

#define REST 0
#define melodyPin 10
// Mario main theme melody

/*int melody[] = {
 *  NOTE_E7, NOTE_E7, 0,       NOTE_E7,
 *  0,       NOTE_C7, NOTE_E7, 0,
 *  NOTE_G7, 0,       0,       0,
 *  NOTE_G6,
 * };
 *
 * /*0,        0,       0,
 *
 * NOTE_C7, 0,        0,       NOTE_G6,
 * 0,       0,        NOTE_E6, 0,
 * 0,       NOTE_A6,  0,       NOTE_B6,
 * 0,       NOTE_AS6, NOTE_A6, 0,
 *
 * NOTE_G6, NOTE_E7,  NOTE_G7,
 * NOTE_A7, 0,        NOTE_F7, NOTE_G7,
 * 0,       NOTE_E7,  0,       NOTE_C7,
 * NOTE_D7, NOTE_B6,  0,       0,
 *
 * NOTE_C7, 0,        0,       NOTE_G6,
 * 0,       0,        NOTE_E6, 0,
 * 0,       NOTE_A6,  0,       NOTE_B6,
 * 0,       NOTE_AS6, NOTE_A6, 0,
 *
 * NOTE_G6, NOTE_E7,  NOTE_G7,
 * NOTE_A7, 0,        NOTE_F7, NOTE_G7,
 * 0,       NOTE_E7,  0,       NOTE_C7,
 * NOTE_D7, NOTE_B6,  0,       0
 * };*/
// Mario main them tempo

/*int tempo[] = {
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *
 *  9,  9,  9,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *
 *  9,  9,  9,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 *  12, 12, 12, 12,
 * };
 */
int melody[] = {
    // Dart Vader theme (Imperial March) - Star wars
    // Score available at https://musescore.com/user/202909/scores/1141521
    // The tenor saxophone part was used

    NOTE_AS4, 8,  NOTE_AS4, 8,  NOTE_AS4, 8, // 1
    NOTE_F5,  2,  NOTE_C6,  2,
    NOTE_AS5, 8,  NOTE_A5,  8,  NOTE_G5,  8, NOTE_F6, 2, NOTE_C6,  4,
    NOTE_AS5, 8,  NOTE_A5,  8,  NOTE_G5,  8, NOTE_F6, 2, NOTE_C6,  4,
    NOTE_AS5, 8,  NOTE_A5,  8,  NOTE_AS5, 8, NOTE_G5, 2, NOTE_C5,  8, NOTE_C5,   8,  NOTE_C5, 8,
    NOTE_F5,  2,  NOTE_C6,  2,
    NOTE_AS5, 8,  NOTE_A5,  8,  NOTE_G5,  8, NOTE_F6, 2, NOTE_C6,  4,

    NOTE_AS5, 8,  NOTE_A5,  8,  NOTE_G5,  8, NOTE_F6, 2, NOTE_C6,  4, // 8
    NOTE_AS5, 8,  NOTE_A5,  8,  NOTE_AS5, 8, NOTE_G5, 2, NOTE_C5,  -8,NOTE_C5,   16,
    NOTE_D5,  -4, NOTE_D5,  8,  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5,  8, NOTE_F5,   8,
    NOTE_F5,  8,  NOTE_G5,  8,  NOTE_A5,  8, NOTE_G5, 4, NOTE_D5,  8, NOTE_E5,   4,  NOTE_C5, -8,NOTE_C5,  16,
    NOTE_D5,  -4, NOTE_D5,  8,  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5,  8, NOTE_F5,   8,

    NOTE_C6,  -8, NOTE_G5,  16, NOTE_G5,  2, REST,    8, NOTE_C5,  8, // 13
    NOTE_D5,  -4, NOTE_D5,  8,  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5,  8, NOTE_F5,   8,
    NOTE_F5,  8,  NOTE_G5,  8,  NOTE_A5,  8, NOTE_G5, 4, NOTE_D5,  8, NOTE_E5,   4,  NOTE_C6, -8,NOTE_C6,  16,
    NOTE_F6,  4,  NOTE_DS6, 8,  NOTE_CS6, 4, NOTE_C6, 8, NOTE_AS5, 4, NOTE_GS5,  8,  NOTE_G5, 4, NOTE_F5,  8,
    NOTE_C6,  1
};

void playAll()
{
    // sing the tunes
    // sing(1);
}

int song = 0;

void sing(int s)
{
    int tempo = 144;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;

    // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
    int wholenote = (60000 * 4) / tempo;

    int divider = 0, noteDuration = 0;

    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
    {
        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0)
        {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        }
        else if (divider < 0)
        {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(melodyPin, melody[thisNote], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(melodyPin);
    }
}

void buzz(long frequency, long length)
{
    //    tone(melodyPin, frequency, 100 * 0.9);
    //    delay(length);
    //    noTone(melodyPin);
    long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
    //// 1 second's worth of microseconds, divided by the frequency, then split in half since
    //// there are two phases to each cycle
    long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing

    //// multiply frequency, which is really cycles per second, by the number of seconds to
    //// get the total number of cycles to produce
    for (long i = 0; i < numCycles; i++) // for the calculated length of time...
    {
        digitalWrite(melodyPin, HIGH); // write the buzzer pin high to push out the diaphram
        delayMicroseconds(delayValue); // wait for the calculated delay value
        digitalWrite(melodyPin, LOW); // write the buzzer pin low to pull back the diaphram
        delayMicroseconds(delayValue); // wait again or the calculated delay value
    }
}

void buzzOff()
{
    digitalWrite(melodyPin, LOW);
}
