    
#include <Wire.h> 
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int switch1 = 6;
const int switch2 = 7;

 int buttonState1 = 0;  
 int buttonState2 = 0;  
 
const int analogIn = A0; //Connect current sensor with A0 of Arduino
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500;
double Voltage = 0; //voltage measuring
double Amps = 0;// Current measuring

const int tempPin = A1; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading

#define pwm 9

byte degree[8] = 
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

void setup()
{
 lcd.begin(16, 2);
 Serial.begin(9600);
 lcd.createChar(1, degree);
 lcd.clear();
 lcd.print("   Fan Speed  ");
 lcd.setCursor(0,1);
 lcd.print("  Controlling ");
 delay(2000);
 analogWrite(pwm, 0);
 lcd.clear();
 lcd.print("Circuit Digest ");
 delay(2000);
   pinMode(tempPin, INPUT);
     pinMode(analogIn, INPUT);
    pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
}

void loop()
{
    buttonState1 = digitalRead(switch1);
    buttonState2 = digitalRead(switch2);
    Amps = readcurrent();
    
if (buttonState1 == LOW )

{
  while(buttonState1 == LOW )
  {
  lcd.clear();

   lcd.print("Auto selected");

   delay(4000);
  analogWrite(pwm, 255);
  lcd.clear();
  lcd.print("Fan Speed: 100%   ");
  delay(100);
  }
 
   
}


  if (buttonState2 == LOW )

  {
   lcd.clear();
  
   lcd.print("Manual selected");
   delay(4000);
   vout = analogRead(tempPin);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
 
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(tempc);   // Printing temperature on LCD
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(0,1);
  if(tempc <26 )
    { 
      analogWrite(9,0);
      lcd.print("Fan OFF            ");
      delay(100);
    }
    
    else if( tempc > 26 && tempc < 27 )
    {
      analogWrite(pwm, 51);
      lcd.print("Fan Speed: 20%   ");
      delay(100);
    }
    
     else if(tempc > 27 && tempc < 28)
    {
      analogWrite(pwm, 102);
      lcd.print("Fan Speed: 40%   ");
      delay(100);
    }
    
     else if(tempc > 28 && tempc < 29)
    {
      analogWrite(pwm, 153);
      lcd.print("Fan Speed: 60%   ");
      delay(100);
    }
    
    else if(tempc > 29 && tempc < 30)
    {
      analogWrite(pwm, 204);
      lcd.print("Fan Speed: 80%    ");
      delay(100);
    }
     else if(tempc>30)
    {
      analogWrite(pwm, 255);
      lcd.print("Fan Speed: 100%   ");
      delay(100);
    } 
  delay(3000);
}

else 
{lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1 for Auto");
  lcd.setCursor(0,1);
  lcd.print("2 for Manual");
  Serial.println("1 for Auto");
  Serial.println("2 for Manual");
  delay(3000);
  
  }
}

int readcurrent()
 {
RawValue = analogRead(analogIn);//reading the value from the analog pin
Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
Amps = ((Voltage - ACSoffset) / mVperAmp);
 }

