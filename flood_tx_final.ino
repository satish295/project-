#include<XBee.h>
#include<SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);
SoftwareSerial XBee(2,3);

int user1 = 11;  //figerprint user 1
int user2 = 12; //figerprint user 2
int motorsw = 8; // gate door switch
int motor = 10;  //gate motor
int buzzer = 9; // buzzer for fake person & high level
 int slow = 5; //sensor low level
 int smedium = 6;  //sensor medium level
  int shigh = 7;  //sensor high level
void setup()
{
   lcd.init();
  lcd.clear();
   lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Flood Detection");
  lcd.setCursor(0,1);
  lcd.print("Using zigbee");
  
  Serial.begin(9600);
  pinMode(user1, INPUT_PULLUP); //figerprint user 1
  pinMode(user2, INPUT_PULLUP); //figerprint user 2
  
  XBee.begin(9600);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8, INPUT_PULLUP);
  
 digitalWrite(motor,HIGH);
  }
  void loop()
{
   int buttonState1 = digitalRead(user1);
   int buttonState2 = digitalRead(user2);
    int buttonState3 = digitalRead(motorsw);
   
      int sensorVal1 = digitalRead(5);
      int sensorVal2 = digitalRead(6);
      int sensorVal3 = digitalRead(7);
  //print out the value of the pushbutton
  Serial.println(sensorVal1);
  Serial.println(sensorVal2);
  Serial.println(sensorVal3);
  
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Finger place");
        lcd.setCursor(0,1);
        lcd.print("for door open");
        delay(2000);
        
  if( (buttonState1 == LOW && buttonState2 == HIGH) || (buttonState1 == HIGH && buttonState2 == LOW )) // fingerprint match
  {
    XBee.write('Z'); 
     delay(1000);
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
    
    if (buttonState3 == LOW) //dam door open 
    {
      
      XBee.write('G'); 
      delay(1000);
      lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dam level-high");
        lcd.setCursor(0,1);
        lcd.print("DOOR OPEN");
        delay(2000);
        digitalWrite(motor,LOW); 
        delay(2000);
      
      }
 else 
   {
     
      digitalWrite(motor,HIGH); 
      }
  }
 else if (buttonState1 == LOW && buttonState2 == LOW) // fingerprint not match
 {
  
  XBee.write('A');
  delay(2000);
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
  
else if (sensorVal1 == HIGH && sensorVal2 == LOW && sensorVal3 == LOW)
{
  
   XBee.write('L');
   delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water level");
    lcd.setCursor(0,1);
    lcd.println("  30%");
  
  }

  else if (sensorVal1 == HIGH && sensorVal2 == HIGH && sensorVal3 == LOW)
{
  
   XBee.write('M');
    delay(1000);
      lcd.clear();
       lcd.setCursor(0,0);
      lcd.print("Water level : 60%");
      lcd.setCursor(0,1);
     lcd.println("  60%");
  }

  else if (sensorVal1 == HIGH && sensorVal2 == HIGH && sensorVal3 == HIGH)
{
  
   XBee.write('H');
   delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water level : 90%");
    lcd.setCursor(0,1);
    lcd.println("  90%");
  
  }
  
    
    
  
}
