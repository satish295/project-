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

 
char c = ' ';

const int buttonPin1 = 2;     //left  the number of the pushbutton pin 
const int buttonPin2 = 3;     //right  the number of the pushbutton pin
const int buttonPin3 = 4;     //brake the number of the pushbutton pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status


void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
    BTserial.begin(9600); //change to match your BT module
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
}
 
void loop()
{
 //delay(5000);
buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
buttonState3 = digitalRead(buttonPin3);
   
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
        if (c == 'O'){
          digitalWrite(LED_BUILTIN, HIGH);
        }
        if (c == 'F'){
          digitalWrite(LED_BUILTIN, LOW);
        }
        //Blinks builtin LED on other Arduino when 'B' is received
        if (c == 'B'){
          digitalWrite(LED_BUILTIN, HIGH);
          delay(200);
          digitalWrite(LED_BUILTIN, LOW);
        }
    }
 
     if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == LOW )              // LEFT 'L'
    {
      c = 'L';
      Serial.println("Button Press D7"); //feedback that button is working
      BTserial.write(c); //sends variable to other board via Bluetooth
      delay(500);
    }

     if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == LOW ) //button on pin D8 acts as shortcut key for character 'B'
    {
      c = 'R';
      Serial.println("Button Press D8"); //feedback that button is working
      BTserial.write(c); //sends variable to other board via Bluetooth
      delay(500);
    }
 

   if (buttonState1 == LOW && buttonState2 == LOW && buttonState3 == HIGH )//button on pin D8 acts as shortcut key for character 'B'
    {
      c = 'B';
      Serial.println("Button Press D9"); //feedback that button is working
      BTserial.write(c); //sends variable to other board via Bluetooth
      delay(500);
    }

if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH ) 
      {
      c = 'C';
      Serial.println("Button Press D9"); //feedback that button is working
      BTserial.write(c); //sends variable to other board via Bluetooth
      delay(500);
    }

    if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == HIGH )
{
      c = 'D';
      Serial.println("Button Press D9"); //feedback that button is working
      BTserial.write(c); //sends variable to other board via Bluetooth
      delay(500);
    }
    
//    
//    if (Serial.available()) // Keep reading from Arduino Serial Monitor and send to HC-05
//    {
//        c =  Serial.read();
//        BTserial.write(c);  
//    }
 
}

