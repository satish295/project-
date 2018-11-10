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
   lcd.backlight();
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
        lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Water level : 30%");
        lcd.setCursor(0,1);
        lcd.write(0);
          
        }
        else if (c == 'M')
        {
          lcd.clear();
          lcd.setCursor(0,0);
         lcd.print("Water level : 60%");
        lcd.setCursor(0,1);
        lcd.write(1);
          
          }
          else if (c == 'H')
          {
           lcd.clear();
           lcd.setCursor(0,0);
         lcd.print("Water level : 90%");
        lcd.setCursor(0,1);
        lcd.write(2);
          }
      else if (c == 'A')
          {
            lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Fingerprint");
        lcd.setCursor(0,1);
        lcd.print("Not Match");
        
         digitalWrite(buzzer,LOW); 
        delay(2000);
         lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Unauthorize");
        lcd.setCursor(0,1);
        lcd.print("person Enter");
        
         digitalWrite(buzzer,LOW); 
        delay(1000);

         digitalWrite(buzzer,LOW); 
          delay(2000);
            }
            else if (c == 'G')
          {
            lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Fingerprint");
        lcd.setCursor(0,1);
        lcd.print("Match");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("authorized");
        lcd.setCursor(0,1);
        lcd.print("person");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dam level-high");
        lcd.setCursor(0,1);
        lcd.print("DOOR OPEN");
        delay(2000);


        
        }
        else
        {
          lcd.clear();
   lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Flood Detection");
  lcd.setCursor(0,1);
  lcd.print("Using zigbee");
          }
}
}

