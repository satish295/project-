#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int input1 = 2;     // the number of the pushbutton pin 2
const int input2 = 3;     // the number of the pushbutton pin 3
const int input3 = 4;     // the number of the pushbutton pin 4
const int input4 = 5;     // the number of the pushbutton pin 5  

const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 10; 

const int relay1 = A0;     // the number of the pushbutton pin 6
const int relay2 = A1;     // the number of the pushbutton pin 7
const int relay3 = A3;     // the number of the pushbutton pin 8
const int relay4 = A4;     // the number of the pushbutton pin 9

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);

      pinMode( 7,OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
lcd.init();
  lcd.backlight();
 lcd.clear();
lcd.setCursor(0,0);
 lcd.print("MultiPower");
 lcd.setCursor(0,1);
lcd.print("Source ");
}

void loop() {
  //read the pushbutton value into a variable
  int sensorVal1 = digitalRead(2);
  int sensorVal2 = digitalRead(3);
  int sensorVal3 = digitalRead(4);
  int sensorVal4 = digitalRead(5);
  
  //print out the value of the pushbutton
  Serial.println(sensorVal1);
   Serial.println(sensorVal2);
    Serial.println(sensorVal3);
     Serial.println(sensorVal4);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal1 == LOW && sensorVal2 == LOW && sensorVal3 == LOW && sensorVal4 == LOW) {
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("All source");
     lcd.setCursor(0,1);
    lcd.print("Available");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Priority source");
    lcd.setCursor(0,1);
    lcd.print("1 ON");
    delay(1000);
digitalWrite(A0,LOW);
  digitalWrite(A1, HIGH);
digitalWrite(A2, HIGH);
 digitalWrite(A3, HIGH);

 digitalWrite(7,LOW);
  digitalWrite(8, HIGH);
digitalWrite(9, HIGH);
 digitalWrite(10, HIGH);
    } 
    
   else if(sensorVal1 == HIGH && sensorVal2 == LOW && sensorVal3 == LOW && sensorVal4 == LOW) {
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("All source");
     lcd.setCursor(0,1);
    lcd.print("Available");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Priority source");
    lcd.setCursor(0,1);
    lcd.print("2 ON");
    delay(1000);
digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
digitalWrite(A2, HIGH);
 digitalWrite(A3, HIGH);

  digitalWrite(7,HIGH);
  digitalWrite(8, LOW);
digitalWrite(9, HIGH);
 digitalWrite(10, HIGH);
Serial.println("Priority source 2 ON");
    }
    else if(sensorVal1 == HIGH && sensorVal2 == HIGH && sensorVal3 == LOW && sensorVal4 == LOW) {
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("All source");
     lcd.setCursor(0,1);
    lcd.print("Available");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Priority source");
    lcd.setCursor(0, 1);
    lcd.print("3 ON");
    delay(1000);
    digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
digitalWrite(A2, LOW);
 digitalWrite(A3, HIGH);

  digitalWrite(7,HIGH);
  digitalWrite(8, HIGH);
digitalWrite(9, LOW);
 digitalWrite(10, HIGH);
 
    Serial.println("Priority source ON");
    }
    else if(sensorVal1 == HIGH && sensorVal2 == HIGH && sensorVal3 == HIGH && sensorVal4 == LOW) {
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("All source");
     lcd.setCursor(0,1);
    lcd.print("Available");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Priority source"); 
    lcd.setCursor(0,1);
    lcd.print("4 ON");
    delay(1000);
    digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
digitalWrite(A2, HIGH);
 digitalWrite(A3, LOW);

  digitalWrite(7,HIGH);
  digitalWrite(8, HIGH);
digitalWrite(9, HIGH);
 digitalWrite(10, LOW);
 
    }
    else if(sensorVal1 == HIGH && sensorVal2 == HIGH && sensorVal3 == HIGH && sensorVal4 == HIGH) {
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("All source");
     lcd.setCursor(0,1);
    lcd.print("is OFF");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ON 4 source");
    lcd.setCursor(0,1);
    lcd.print("Available");
    delay(1000);

digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);

    digitalWrite(7,HIGH);
  digitalWrite(8, HIGH);
digitalWrite(9, HIGH);
 digitalWrite(10, HIGH);
    }
}
