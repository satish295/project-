#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  
#include<XBee.h>
#include<SoftwareSerial.h>
SoftwareSerial XBee(2,3);
char c = ' ';

int buzzer = 9; // buzzer for fake person & high level
int Llevel = 5;
int Mlevel = 6;
int Hlevel = 7;



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
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
}

void loop() {
   if (XBee.available())
    {  
       c = XBee.read();
       if (c == 'L')
       {
        lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Water level");
        lcd.setCursor(0,1);
       lcd.println("  30%");
       digitalWrite(5,LOW); 
          
        }
        else if (c == 'M')
        {
          lcd.clear();
          lcd.setCursor(0,0);
         lcd.print("Water level : 60%");
        lcd.setCursor(0,1);
       lcd.println("  60%");
           digitalWrite(5,LOW); 
           digitalWrite(6,LOW); 
          }
          else if (c == 'H')
          {
           lcd.clear();
           lcd.setCursor(0,0);
         lcd.print("Water level : 90%");
         lcd.setCursor(0,1);
       lcd.println("  90%");
       
       digitalWrite(5,LOW); 
       digitalWrite(6,LOW); 
       digitalWrite(7,LOW); 
         digitalWrite(buzzer,LOW); 
        delay(5000);

         
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
        lcd.print("Dam level-high");
        lcd.setCursor(0,1);
        lcd.print("DOOR OPEN");
        delay(2000);


        
        }

         else if (c == 'Z')
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

