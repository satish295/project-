#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    10
CRGB leds[NUM_LEDS];

const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;     // the number of the pushbutton pin
const int buttonPin3 = 4;     // the number of the pushbutton pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status


void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
}
void loop() {
 
  //delay(5000);
buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
buttonState3 = digitalRead(buttonPin3);

   if (buttonState1 == LOW) {
    // turn LED on:
     for (int i = 7; i <= 9; i++) {
    leds[i] = CRGB ( 0, 0,255);
    FastLED.show();
    delay(100);
  }

  for (int i = 7; i <= 9; i++){
  leds[i] = CRGB::Black;
 FastLED.show();
 delay(100);
    }
   
  }
  else{
    leds[7] = CRGB::Black;
  leds[8] = CRGB::Black;
 leds[9] = CRGB::Black;
    }

   if (buttonState2 == LOW)
   {
    for (int i = 2; i >= 0; i--) {
    leds[i] = CRGB ( 0, 0,255);
    FastLED.show();
    delay(100);
  }
   
    for (int i = 2; i >= 0; i--) {
      leds[i] = CRGB::Black;
 FastLED.show();
 delay(100);
    }
   }
    else
    {
      leds[0] = CRGB::Black;
 leds[1] = CRGB::Black;
 leds[2] = CRGB::Black;
      
      }
    
    

    if (buttonState3 == LOW)
    {
 
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
 FastLED.show();
  delay(500);
    
    }
  else
  {
     leds[0] = CRGB::Black;
 leds[1] = CRGB::Black;
 leds[2] = CRGB::Black;
 leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
 leds[5] = CRGB::Black;
 leds[6] = CRGB::Black;
 leds[7] = CRGB::Black;
  leds[8] = CRGB::Black;
 leds[9] = CRGB::Black;

    }

    }
    

