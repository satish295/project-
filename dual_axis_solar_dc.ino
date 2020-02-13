#include <LiquidCrystal.h>
#include <SimpleDHT.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pinDHT11 = 12;
SimpleDHT11 dht11(pinDHT11);

int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int M1 = 8;
int M11 = 9;
int M2 = 10;
int M22 = 11;
int threshold = 750;
void setup(){
  pinMode (sensor1, INPUT);
  pinMode (sensor2, INPUT);
  pinMode (sensor3, INPUT);
  pinMode (sensor4, INPUT);
  pinMode (M1, OUTPUT);
   pinMode (M11, OUTPUT);
    pinMode (M2, OUTPUT);
     pinMode (M22, OUTPUT);

     lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print(" Dual Axis");
  lcd.setCursor(0, 1);
  lcd.print(" solar control");
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
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    //return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}

if (analogValue1 > threshold && analogValue2 < threshold && analogValue3 < threshold && analogValue4 < threshold) {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
    Serial.print("Sensor 1 "); // RIGHT DIRECTION BOTTOM 
    lcd.clear();
     lcd.setCursor(0, 0);
  lcd.print("LDR 1");
 
  delay(175);
  
  }
//  else {
//    digitalWrite(led1, LOW);
//}
else if (analogValue1 < threshold && analogValue2 > threshold && analogValue3 < threshold && analogValue4 < threshold) {
    digitalWrite(M1, LOW);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
    lcd.clear();
    Serial.print("Sensor 2 "); //LEFT DIRECTION BOTTOM
     lcd.setCursor(0, 0);
  lcd.print("LDR 2");
  
  delay(175);
  } 
//  else {
//    digitalWrite(led2, LOW);
//}
else if (analogValue1 < threshold && analogValue2 < threshold && analogValue3 > threshold && analogValue4 < threshold) {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, LOW);
     lcd.clear();
     Serial.print("Sensor 3 ");  // 
     lcd.setCursor(0, 0);
  lcd.print("LDR 3");

  delay(30);
//  digitalWrite(M1, HIGH);
//    digitalWrite(M11, HIGH);
//    digitalWrite(M2, HIGH);
//    digitalWrite(M22, HIGH);
  } 
//  else {
//    digitalWrite(led3, LOW);
//}
else if (analogValue1 < threshold && analogValue2 < threshold && analogValue3 < threshold && analogValue4 > threshold) {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M22, HIGH);
    lcd.clear();
    Serial.print("Sensor 4 "); 
     lcd.setCursor(0, 0);
  lcd.print("LDR 4");
  delay(250);
  digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
  } 
else {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
    lcd.clear();
     lcd.setCursor(0, 0);
  lcd.print("Not detect ");
  Serial.print("sensor not detect");
  delay(50);
}
}
