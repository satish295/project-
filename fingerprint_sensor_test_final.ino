/*
  fingerprint.ino

  Author:Vigoss.kk
  www.elecrow.com
  2013-10-6
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//int sensorVal1 = 0;
//int sensorVal2 = 0;
const int input3 = 4;     // the number of the pushbutton pin 4
//const int input4 = 5;     // the number of the pushbutton pin 5  
const int buzzer = 5;//buzzer
const int relay1 = 6;     // motor1
const int relay2 = 7;     //motor2

SoftwareSerial mySerial(2, 3);                                // tx, rx

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
   lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
   lcd.print("Place finger");
   lcd.setCursor(0,1);
  lcd.print("for start");
  pinMode(4, INPUT_PULLUP);
 
    pinMode(5, OUTPUT);//buzzer output
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    Serial.begin(9600);
    finger.begin(9600);
    delay(500);
    Serial.print("setup ok!");
     digitalWrite(5, LOW);
    
}

void loop()                     // run over and over again
{
  int sensorVal1 = digitalRead(4);
 // int sensorVal2 = digitalRead(5);
  
  
  getFingerprintID();
    if(getFingerprintIDez()>=0)
    {
      startmotor();
      }
    delay(50);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
     // Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
    //  Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    startmotor();
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
//  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
//  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez()
{

    if (!finger.verifyPassword())
    {
        Serial.print("Did not find fingerprint sensor :(");
        return -1;
    }

    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)
    {
        return -1;
    }

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)
    {
        return -1;
    }

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)
    {
        return -1;
    }

    Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
   // DBG(finger.confidence);
   Serial.println(finger.confidence);


    return finger.fingerID;

}

void startmotor()
{
  {
      lcd.clear();
      lcd.setCursor(0,0);
   lcd.print("finger match");
   lcd.setCursor(0,1);
  lcd.print("vehicle start");

  delay(5000);
       Serial.print("Control motor direction");
   if (digitalRead(input3) == LOW )
   {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
     Serial.print("Forward");
      digitalWrite(5, HIGH);
    }

  else 

  {
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
     Serial.print("Reverse");
      digitalWrite(5,HIGH);
    }
        
    }
  
  
  }

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
