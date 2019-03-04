#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int switch1 = 6;
const int switch2 = 7;

 int buttonState1 = 0;  
 int buttonState2 = 0;  
 

const int tempPin = A1; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading

int voltage = 230;
int pf = 0.3;

double sumWH = 0.00000;
float WH = 0;//energy consumption in watt hour 
double sumRupees = 0.00000;//Total energy consumption in rupees 
float rupees = 0;//energy consumption in rupees
double power = 0;//


const int sensorIn = A0;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

#define fan 9
#define bulb 8

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
  lcd.init();
 Serial.begin(9600);
 lcd.backlight();
 lcd.createChar(1, degree);
 lcd.clear();
 lcd.print(" power consume");
 lcd.setCursor(0,1);
 lcd.print("  Controlling ");
 delay(2000);
  pinMode(fan, OUTPUT);
  pinMode(bulb, OUTPUT);
 lcd.clear();
 lcd.print("power consume ");
 delay(2000);
   pinMode(tempPin, INPUT);
  
    pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
    digitalWrite(fan, LOW);
  digitalWrite(bulb, LOW);
}

void loop()
{
    buttonState1 = digitalRead(switch1);
    buttonState2 = digitalRead(switch2);
   Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS);
 Serial.println(" A");

   vout = analogRead(tempPin);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
 
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(tempc);   // Printing temperature on LCD
  lcd.write(1);
  
  Serial.print(tempc);   // Printing temperature on LCD
  lcd.print("C");
  delay(2000);
    
if (buttonState1 == LOW )

{
  while(buttonState1 == LOW )
  {
  lcd.clear();

   lcd.print("Auto selected");
Serial.print("Auto selected");
   delay(2000);
  digitalWrite(fan, HIGH);
  digitalWrite(bulb, HIGH);
Serial.print("Auto selected");
Serial.print("both on");
  lcd.clear();
// lcd.print(tempc);
 lcd.setCursor(0,1);
 lcd.print("Current = ");
 lcd.setCursor(10,1);
 lcd.print(AmpsRMS);
  delay(30000);
 lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Voltage = 230v");
  lcd.setCursor(0,1);
  lcd.print("current = ");
  lcd.setCursor(10,1);
  lcd.print(AmpsRMS);
  delay(2000);
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("power");
  lcd.setCursor(10,0);
  lcd.print("8 Watt");
  lcd.setCursor(0,1);
  lcd.print("totalRS=4 Ruppes");
  delay(2000);
  
  
  
  }
 
   
}


  if (buttonState2 == LOW )

  {
    while(buttonState2 == LOW )
    {
   lcd.clear();
  
   lcd.print("Manual selected");
   Serial.print("Manual selected");
   delay(4000);
 
  lcd.setCursor(0,1);
  digitalWrite(fan, HIGH);
  digitalWrite(bulb, HIGH);
  if(tempc <26 )
    { 
       digitalWrite(fan, LOW);
       digitalWrite(bulb, LOW);
      lcd.print(tempc);
      delay(2000);
       lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("power");
  lcd.setCursor(10,0);
  lcd.print("8 Watt");
  lcd.setCursor(0,1);
  lcd.print("totalRS=0 Ruppes");
  delay(2000);
  
    }
    
    else if( tempc > 28 && tempc <  29)
    {
       digitalWrite(bulb, HIGH);
      lcd.print(tempc); 
      delay(100);
    }
    
     else if(tempc > 29 && tempc < 31)
    {
       digitalWrite(bulb, HIGH);
       digitalWrite(fan,HIGH);
             lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("power");
  lcd.setCursor(10,0);
  lcd.print("8 Watt");
  lcd.setCursor(0,1);
  lcd.print("totalRS=1.5 Ruppes");
  delay(2000);
    }
    
   
     else if(tempc>32)
    {
       digitalWrite(bulb, LOW);
       digitalWrite(fan,HIGH);
        lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("power");
  lcd.setCursor(10,0);
  lcd.print("8 Watt");
  lcd.setCursor(0,1);
  lcd.print("totalRS=2 Ruppes");
  delay(2000);
  
     
    } 
  delay(3000);
}
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

float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
