#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    10
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}
void loop() {
 
  //delay(5000);
 
  for (int i = 7; i <= 9; i++) {
    leds[i] = CRGB ( 0, 0,255);
    FastLED.show();
    delay(200);
  }
 for (int i = 2; i >= 0; i--) {
    leds[i] = CRGB ( 0, 0,255);
    FastLED.show();
    delay(200);
  }
    for (int i = 7; i <= 9; i++){
  
 leds[i] = CRGB::Black;
 FastLED.show();
 delay(100);
    }
    for (int i = 2; i >= 0; i--) {
      leds[i] = CRGB::Black;
 FastLED.show();
 delay(100);
    }

    
 leds[3] = CRGB::Red;
 leds[4] = CRGB::Red;
 leds[5] = CRGB::Red;
 leds[6] = CRGB::Red;
  FastLED.show();
  delay(1000);

  leds[3] = CRGB::Black;
 leds[4] = CRGB::Black;
 leds[5] = CRGB::Black;
 leds[6] = CRGB::Black;
    }

