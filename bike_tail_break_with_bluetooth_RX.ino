// Basic Bluetooth sketch HC-05_AT_MODE_01
// Connect the HC-05 module and communicate using the serial monitor
//
// The HC-05 defaults to commincation mode when first powered on you will need to manually enter AT mode
// The default baud rate for AT mode is 38400 - JSC changed to 9600
// See www.martyncurrey.com for details 
//[http://www.martyncurrey.com/connecting-2-arduinos-by-bluetooth-using-a-hc-05-and-a-hc-06-easy-method-using-cmode/]
//
//Modified by Satish Lakhan 9/17/2018 for remote control functionality:
//now works if you send one serial command (O or F) the other board then turns on/off light along with B that
//blinks lights. Button on D8 acts as a shortcut for the character B, creating a rudimentary remote control.
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    10
CRGB leds[NUM_LEDS]; 
 
char c = ' ';


void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
    BTserial.begin(38400); //change to match your BT module
  //  pinMode(LED_BUILTIN, OUTPUT);
//    pinMode(buttonPin1, INPUT);
//    pinMode(buttonPin2, INPUT);
//    pinMode(buttonPin3, INPUT);
FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
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
  FastLED.show();

}
 
void loop()
{
// buttonState1 = digitalRead(buttonPin1); //reads pushbutton value  
// 
// buttonState2 = digitalRead(buttonPin2); //reads pushbutton value  
//
// buttonState3 = digitalRead(buttonPin3); //reads pushbutton value  
 // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
        if (c == 'L')
        {
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

        
        if (c == 'R')                  
        {                                              //RIGHT
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
                                       
  if (c == 'B')
  {
 
 leds[3] = CRGB::Red;
 leds[4] = CRGB::Red;
 leds[5] = CRGB::Red;
 leds[6] = CRGB::Red;
  FastLED.show();                        //BREAK
  delay(500);

 leds[3] = CRGB::Black;
 leds[4] = CRGB::Black;
 leds[5] = CRGB::Black;
 leds[6] = CRGB::Black;
 FastLED.show();
  delay(200);
    
    }
                                      
        
  if (c == 'C')
  {
       for (int i = 7; i <= 9; i++) {
    leds[i] = CRGB ( 0, 0,255);
    FastLED.show();
    delay(100);
  }

  for (int i = 7; i <= 9; i++){                             //LEFT & BREAK
  leds[i] = CRGB::Black;
 FastLED.show();
 delay(100);
    }
      {
 
 leds[3] = CRGB::Red;
 leds[4] = CRGB::Red;
 leds[5] = CRGB::Red;
 leds[6] = CRGB::Red;
  FastLED.show();
  delay(500);

 leds[3] = CRGB::Black;
 leds[4] = CRGB::Black;
 leds[5] = CRGB::Black;
 leds[6] = CRGB::Black;
 FastLED.show();
  delay(200);
    
   } 
       }
                  
                                   
   if (c == 'D')
     {
       for (int i = 2; i >= 0; i--) {          //RIGHT & BREAK
    leds[i] = CRGB ( 0, 0,255);
    FastLED.show();
    delay(100);
  }
   
    for (int i = 2; i >= 0; i--) {
      leds[i] = CRGB::Black;
 FastLED.show();
 delay(100);
    }
  
      {
 
 leds[3] = CRGB::Red;
 leds[4] = CRGB::Red;
 leds[5] = CRGB::Red;
 leds[6] = CRGB::Red;
  FastLED.show();
  delay(500);

 leds[3] = CRGB::Black;
 leds[4] = CRGB::Black;
 leds[5] = CRGB::Black;
 leds[6] = CRGB::Black;
 FastLED.show();
  delay(200);
    
    } 
      
      
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
 
    
    
//    if (Serial.available()) // Keep reading from Arduino Serial Monitor and send to HC-05
//    {
//        c =  Serial.read();
//        BTserial.write(c);  
//    }
 
}

