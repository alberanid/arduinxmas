/*
 * Arduino Christmas Tree - Arduino-powered Christmas tree.
 *
 * The proximity sensor is used to set the rate of the blinking LEDs.
 *
 * Copyright (c) 2013 Davide Alberani <da@erlug.linux.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

const int NR_OF_LEDS = 3;
const int DISTANCE_PIN = 0;
int DIVIDER = 1;

struct led {
  int pin;
  bool on;
};

// Add more LEDs here, if needed.
led LEDS[] = {{9, false}, {10, false}, {11, false}};


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int i = 0; i < NR_OF_LEDS; i++) {
    pinMode(LEDS[i].pin, OUTPUT);
  }
}


bool flip() {
  return (bool) random(2);
}


/** Check the distance from the sensor and modify the divider accordingly. */
void checkDistance() {
  int distance = analogRead(DISTANCE_PIN);
  DIVIDER = map(distance, 30, 600, 1, 25);
  if (DIVIDER < 1) {
    DIVIDER = 1;
  }
}


/** Turn a LED on or off. */
void switchLED(struct led* aled) {
  if (!flip()) {
    return;
  }
  int add = 1;
  int value = 0;
  if (aled->on) {
    add = -1;
    value = 255;
  }
  for (int i = 0; i < 256; i++) {
    analogWrite(aled->pin, value);
    value += add;
    delay(20/DIVIDER);
  }
  aled->on = !aled->on;
  checkDistance();
}


void loop() {
  for (int i = 0; i < NR_OF_LEDS; i++) {
    switchLED(&(LEDS[i]));
  }
  delay(2000/DIVIDER);
}

