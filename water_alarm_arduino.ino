#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int led1 = 8;
int led2 = 9;
int led3 = 10;
int relay = 11;
int threshold = 150;
void setup(){
  pinMode (sensor1, INPUT);
  pinMode (sensor2, INPUT);
  pinMode (sensor3, INPUT);
  pinMode (sensor4, INPUT);
  pinMode (led1, OUTPUT);
   pinMode (led2, OUTPUT);
    pinMode (led3, OUTPUT);
     pinMode (relay, OUTPUT);

     lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Water Level");
  lcd.setCursor(0, 1);
  lcd.print("Indicator");
  Serial.begin(9600);
  
}
void loop(){
 int analogValue1 = analogRead(sensor1);
int analogValue2 = analogRead(sensor2);
int analogValue3 = analogRead(sensor3);
int analogValue4 = analogRead(sensor4);
Serial.println(analogValue1);
Serial.println(analogValue2);
Serial.println(analogValue3);
Serial.println(analogValue4);
delay(1000);


if (analogValue1 > threshold && analogValue2 < threshold && analogValue3 < threshold && analogValue4 < threshold) {
    digitalWrite(led1, HIGH);
    lcd.clear();
     lcd.setCursor(0, 0);
  lcd.print("Level:25%");
 Serial.println("Water Level:25%");
  delay(1000);
  }
//  else {
//    digitalWrite(led1, LOW);
//}
else if (analogValue1 > threshold && analogValue2 > threshold && analogValue3 < threshold && analogValue4 < threshold) {
    digitalWrite(led2, HIGH);
    lcd.clear();
     lcd.setCursor(0, 0);
  lcd.print("Level:50%");
  Serial.println("Water Level:50%");
  delay(1000);
  } 
//  else {
//    digitalWrite(led2, LOW);
//}
else if (analogValue1 > threshold && analogValue2 > threshold && analogValue3 > threshold && analogValue4 < threshold) {
    digitalWrite(led3, HIGH);
     lcd.clear();
     lcd.setCursor(0, 0);
  lcd.print("Level:75%");
  Serial.println("Water Level:75%");
  delay(1000);
  } 
//  else {
//    digitalWrite(led3, LOW);
//}
else if (analogValue1 > threshold && analogValue2 > threshold && analogValue3 > threshold && analogValue4 > threshold) {
    digitalWrite(relay, HIGH);
    lcd.clear();
     lcd.setCursor(0, 0);
  lcd.print("Level:100%");
  Serial.println("Water Level:100%");
  delay(1000);
  } 
else {
   digitalWrite(relay, LOW);
    lcd.clear();
     lcd.setCursor(0, 0);
  lcd.print("No water");
  Serial.print("No Water");
  delay(1000);
}
}
