#include <FastLED.h>

#define NUM_LEDS 12
#define DATA_PIN 5

#define POT_PIN A0
#define POT_DEBOUNCE 5
#define POT_MAX 1023
#define NUM_BUCKETS 10

#define BUTTON_PIN 13

#define MINIMUM_TIME 2

// Define the array of leds
CRGB leds[NUM_LEDS];
int inTime = MINIMUM_TIME;
int potValue;
float potBuckets = POT_MAX / NUM_BUCKETS;

bool pI() {
  bool repeat = true;
  bool newValueSet = false;
  while (repeat) {
    int newPotValue = analogRead(POT_PIN);
    int potDiff = abs(potValue - newPotValue);
    if (int(potValue / potBuckets) + MINIMUM_TIME != int(newPotValue / potBuckets) + MINIMUM_TIME) {
      repeat = true;
      newValueSet = true;
      potValue = newPotValue;
      inTime = int(potValue / potBuckets) + MINIMUM_TIME;
      FastLED.clear();
      for(int i=0; i<inTime; i++) {
        leds[i] = CRGB::White;
      }
      FastLED.show();
      delay(2000);
      FastLED.clear();
    } else {
      repeat = false;
    }
  }
  return newValueSet;
}

void setup() { 
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
}

void loop() { 
  FastLED.clear();
  if (pI()) return;
  double lightUnit = inTime * 1000 / 12;
  // Set lights blue
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
    if (pI()) return;
  }
  FastLED.show();
  delay(500);

  // Breathe in
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Green;
    FastLED.show();
    if (pI()) return;
    delay(lightUnit);
  }

  // Second breath
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
    FastLED.show();    
    if (pI()) return;
  }
  delay(500);

  // Breathe out
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    if (pI()) return;
    delay(lightUnit * 2);
  }
  delay(500);
}
