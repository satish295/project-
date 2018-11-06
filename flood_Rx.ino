#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  
#include<XBee.h>
#include<SoftwareSerial.h>
SoftwareSerial XBee(2,3);
char c = ' ';

int buzzer = 9; // buzzer for fake person & high level
byte customCharL[] = {
  B00000,
  B00000,
  B00000,
  B00000,  //LOW WATER LEVEL
  B00000,
  B00000,
  B11111,
  B11111
};
byte customCharM[] = {
  B00000,
  B00000,
  B00000,
  B11111,   //MEDIUM WATER LEVEL
  B11111,
  B11111,
  B11111,
  B11111
};

byte customCharH[] = {
  B11111,
  B11111,
  B11111, //HIGH WATER LEVEL
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};


void setup() {
  lcd.init();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Flood Detection");
  lcd.setCursor(0,1);
  lcd.print("Using zigbee");
XBee.begin(9600);
Serial.begin(9600);
pinMode(9,OUTPUT);
digitalWrite(buzzer,HIGH); 
lcd.createChar(0, customCharL);
lcd.createChar(1, customCharM);
lcd.createChar(2, customCharH);
}

void loop() {
   if (XBee.available())
    {  
       c = XBee.read();
       if (c == 'L')
       {
          
        }
        else if (c == 'M')
        {
          
          }
          else if (c == 'H'){
          
          }
        }
}

