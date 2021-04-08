#include <Arduino.h>
#include <Encoder.h>
#include <Keyboard.h>

/**
 * Change these pin numbers to the pins connected to your encoder:
 *   Best Performance: both pins have interrupt capability
 *   Good Performance: only the first pin has interrupt capability
 *   Low Performance:  neither pin has interrupt capability
 *
 * Avoid using pins with LEDs attached!
 */

#ifndef PIN_HOR_1
#define PIN_HOR_1 2
#endif
#ifndef PIN_HOR_2
#define PIN_HOR_2 3
#endif
#ifndef NUM_STEPS_HOR
#define NUM_STEPS_HOR 4
#endif
#ifndef KEY_DEC_HOR
#define KEY_DEC_HOR KEY_LEFT
#endif
#ifndef KEY_INC_HOR
#define KEY_INC_HOR KEY_RIGHT
#endif

#ifndef PIN_VER_1
#define PIN_VER_1 11
#endif
#ifndef PIN_VER_2
#define PIN_VER_2 12
#endif
#ifndef NUM_STEPS_VER
#define NUM_STEPS_VER 4
#endif
#ifndef KEY_DEC_VER
#define KEY_DEC_VER KEY_DOWN
#endif
#ifndef KEY_INC_VER
#define KEY_INC_VER KEY_UP
#endif

Encoder knobHor(PIN_HOR_1, PIN_HOR_2);
Encoder knobVer(PIN_VER_1, PIN_VER_2);

int32_t lastHorPos = 0;
int32_t lastVerPos = 0;

void setup() {}

void processKnob(Encoder &knob, int32_t &lastPos, int32_t numSteps,
                 int32_t decKey, int32_t incKey) {
  int32_t posOffset = knob.readAndReset();
  lastPos += posOffset;
  while (lastPos <= -numSteps) {
    Keyboard.press(decKey);
    Keyboard.release(decKey);
    lastPos += numSteps;
  }
  while (lastPos >= numSteps) {
    Keyboard.press(incKey);
    Keyboard.release(incKey);
    lastPos -= numSteps;
  }
}

void loop() {
  processKnob(knobHor, lastHorPos, NUM_STEPS_HOR, KEY_DEC_HOR, KEY_INC_HOR);
  processKnob(knobVer, lastVerPos, NUM_STEPS_VER, KEY_DEC_VER, KEY_INC_VER);
}
