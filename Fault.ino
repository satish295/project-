#include "OneButton.h"                              //we need the OneButton library
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
 
OneButton button(A1, true);                         //attach a button on pin A1 to the library
 
int R = 10;
int Y = 11;
int B = 12;
 
void setup() {
 
      
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Three Phase");
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("Fault Analysis");
  pinMode(10, OUTPUT);                              // sets the digital pin as output
  pinMode(11, OUTPUT);                              // sets the digital pin as output
  pinMode(12, OUTPUT);
     
  //button.attachDoubleClick(doubleclick);            // link the function to be called on a doubleclick event.
  button.attachClick(singleclick);                  // link the function to be called on a singleclick event.
  button.attachLongPressStop(longclick);            // link the function to be called on a longpress event.
  Serial.begin(9600);
} 
  
 
 
void loop() {
  digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(11, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(12,LOW );   // turn the LED on (HIGH is the voltage level)
  button.tick();                                    // check the status of the button
 
 
  delay(10);                                        // a short wait between checking the button
} // loop
 
 
 
//void doubleclick() {                                // what happens when button is double-clicked
 //digitalWrite(11,HIGH);                             // light the green LED
 //delay(1000);                                       // wait one second
 //digitalWrite(11,LOW);                              // turn off green LED

 //Serial.print("double trip");
//} 
 
void singleclick(){ 
 lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
lcd.print("Temporary Fault");                                // what happens when the button is clicked

digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
 Serial.print("Relay ON");
delay(1000);
 Serial.print("single trip");
digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
digitalWrite(11, LOW);   // turn the LED on (HIGH is the voltage level)
digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
 Serial.print("Relay OFF");
lcd.print("ALL OK");                                // what happens when the button is clicked
 
}
 
void longclick(){                                   // what happens when buton is long-pressed

lcd.clear();
lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
lcd.print("permanent Fault");
lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
lcd.print("Check Fault");
digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
Serial.print("permanant trip");
Serial.print("Relay ON");
delay(15000);
}