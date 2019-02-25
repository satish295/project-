#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

 unsigned long time;
const int switch1 = 3;
const int switch2 = 4;

 int buttonState1 = 0;  
 int buttonState2 = 0;  
 
int tempPin = A0;   // the output pin of LM35
int fan = 11;       // the pin where fan is
int led = 8;        // led pin
int temp;
int current;
int tempMin = 30;   // the temperature to start the fan 0%
int tempMax = 60;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;
int meter;

//Measuring Current Using ACS712
 
const int analogIn = 0; //Connect current sensor with A0 of Arduino
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500;
double Voltage = 0; //voltage measuring
double Amps = 0;// Current measuring


void setup() {
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(tempPin, INPUT);
  lcd.init();
  lcd.clear();
   lcd.backlight(); 
  Serial.begin(9600);

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() 
//temp measure
  {
      buttonState1 = digitalRead(switch1);
      buttonState2 = digitalRead(switch2);

      if (buttonState1 == LOW )
      {
        
    time = millis();
     //prints time since program started
    Serial.println(time);
  // wait a second so as not to send massive amounts of data
     delay(1000);
Amps = readcurrent();
Serial.print(Amps);

 meter = (((time / 25000)* Amps)+(temp / 0.06)) ;  
 Serial.println(meter);
        
      }

      
  if (buttonState2 == LOW )
      {
        
    time = millis();
     //prints time since program started
    Serial.println(time);
  // wait a second so as not to send massive amounts of data
     delay(1000);
 Amps = readcurrent();
  Serial.print(Amps);

 meter = (((time / 32000)* Amps)+(temp / 0.02)) ;  
 Serial.println(meter);

    temp = readTemp();     // get the temperature
   Serial.print( temp );
   Serial.println("  C ");
    if(temp > tempMax) // if temp is higher than tempMax
     {        
     digitalWrite(led, LOW);  // turn on led 
     } 
   else               // else turn of led
     {                    
     digitalWrite(led, HIGH); 
     }

        }
      
   temp = readTemp();     // get the temperature
   Serial.print( temp );
   Serial.println("  C ");
   if(temp < tempMin)     // if temp is lower than minimum temp
   {   
       fanSpeed = 0;      // fan is not spinning
       analogWrite(fan, fanSpeed); 
       fanLCD=0;
       digitalWrite(fan, LOW);       
   }
  } 
 

int readTemp() {  // get the temperature and convert it to celsius
  temp = analogRead(tempPin);
  return temp * 0.48828125;
}

int readcurrent()
 {
RawValue = analogRead(analogIn);//reading the value from the analog pin
Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
Amps = ((Voltage - ACSoffset) / mVperAmp);
//Prints on the serial port
Serial.print("Raw Value = " ); // prints on the serial monitor
Serial.print(RawValue); //prints the results on the serial monitor
lcd.clear();//clears the display of LCD
delay(1000);//delay of 1 sec
lcd.display();
lcd.setCursor(1,0);
lcd.print("Raw Value = ");
lcd.setCursor(13,0);
lcd.print(RawValue);
Serial.print("\t mV = "); // shows the voltage measured
Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
lcd.setCursor(1,1);
lcd.print("Voltage = ");
lcd.setCursor(11,1);
lcd.print(Voltage,3);
lcd.setCursor(17,1);
lcd.print("mV");//Unit for the voltages to be measured
Serial.print("\t Amps = "); // shows the voltage measured
Serial.println(Amps,3);// the '3' after voltage allows you to display 3 digits after decimal point
lcd.setCursor(1,2);
lcd.print("Current = ");
lcd.setCursor(11,2);
lcd.print(Amps,3);
lcd.setCursor(16,2);
lcd.print("A"); //unit for the current to be measured
delay(2500); //delay of 2.5 sec
} 
