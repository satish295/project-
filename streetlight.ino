/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// constants won't change. They're used here to set pin numbers:
const int IRSensor1 = 7; // connect IR sensor module to Arduino pin D5
const int IRSensor2 = 8; // connect IR sensor module to Arduino pin D5
const int IRSensor3 = 9 ; // connect IR sensor module to Arduino pin D5

const int ledPin1 =  3;      // the number of the LED pin
const int ledPin2 =  5;      // the number of the LED pin
const int ledPin3 =  6;      // the number of the LED pin
// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
}

void loop() {
  // read the state of the pushbutton value:
  unsigned int AnalogValue;

AnalogValue = analogRead(A0);

Serial.println(AnalogValue);

  buttonState1 = digitalRead(IRSensor1);
  buttonState2 = digitalRead(IRSensor2);
  buttonState3 = digitalRead(IRSensor3);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    // turn LED on:
    analogWrite(ledPin1, 255);
  } 
  if (buttonState2 == HIGH) {
    // turn LED on:
    analogWrite(ledPin2, 255);
  } 
  if (buttonState3 == HIGH) {
    // turn LED on:
    analogWrite(ledPin3, 255);
  } 
  else {
    // turn LED off:
    analogWrite(ledPin1, 100);
    analogWrite(ledPin2, 100);
    analogWrite(ledPin3, 100);
  }
}
