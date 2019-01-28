
// defines pins numbers
#include "UbidotsMicroESP8266.h"
#define ID "5a522ab6c03f97075a5290b0" 

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

// this constant won't change:
const int  buttonPin = 5;    // the pin that the pushbutton is attached to
const int ledPin = 4;       // the pin that the LED is attached to
const int sensorIn = A0;
int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module

int power;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

#define TOKEN "A1E-hrO1ghW9IulH49COXNRkc47N6FbTFD"
#define WIFISSID "virus" // Change this for your WiFi User 
#define PASSWORD "EXTC2016" // Change this for your WiFi pass 

Ubidots client(TOKEN);

void setup() {
 Serial.begin( 115200);
delay(10);
Serial.println(" Sensor Test!");
client.wifiConnection(WIFISSID,PASSWORD);
 
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  pinMode(sensorIn, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:

}
void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of pulses:  ");
      Serial.println(buttonPushCounter);
    
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  
   
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");
  float power = AmpsRMS*buttonPushCounter;

  if(isnan(power) )
   { 
    Serial.println(" Failed to read from current sensor!");
   return; 
   }
   client.add(ID,power);
   client.sendAll();
   Serial.print("Power: ");
   Serial.println(power);
}
float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }

  
   
    
