#include <FastLED.h>

#define NUM_LEDS 12
#define DATA_PIN 5
#define MINIMUM_TIME 2
#define IN_TIME 5

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
}

void loop() { 
  double lightUnit = IN_TIME * 1000 / 12;

  // Set lights blue
  for(int i=0; i<NUM_LEDS; i++) {

    leds[i] = CRGB::Blue;
    FastLED.show();
  }
  delay(500);

  // Breathe in
  for(int i=0; i<NUM_LEDS; i++) {

    leds[i] = CRGB::Green;
    FastLED.show();
    delay(lightUnit);
  }

  // Second breath
  for(int i=0; i<NUM_LEDS; i++) {

    leds[i] = CRGB::Blue;
    FastLED.show();
  }
  delay(500);

  // Breathe out
  for(int i=0; i<NUM_LEDS; i++) {

    leds[i] = CRGB::Red;
    FastLED.show();
    delay(lightUnit * 2);
  }
  delay(500);
}
