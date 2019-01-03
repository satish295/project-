
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); 
 
int tempPin = A1;   // the output pin of LM35
int fan = 11;       // the pin where fan is
int led = 8;        // led pin
int temp;
int tempMin = 30;   // the temperature to start the fan 0%
int tempMax = 60;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;

//Measuring Current Using ACS712
 
const int analogIn = 0; //Connect current sensor with A0 of Arduino
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
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
}

void loop() 
//temp measure
  {  
   temp = readTemp();     // get the temperature
   Serial.print( temp );
   if(temp < tempMin)     // if temp is lower than minimum temp
   {   
       fanSpeed = 0;      // fan is not spinning
       analogWrite(fan, fanSpeed); 
       fanLCD=0;
       digitalWrite(fan, LOW);       
   } 
   if((temp >= tempMin) && (temp <= tempMax)) // if temperature is higher than minimum temp
   {  
       fanSpeed = temp;//map(temp, tempMin, tempMax, 0, 100); // the actual speed of fan//map(temp, tempMin, tempMax, 32, 255);
       fanSpeed=1.5*fanSpeed;
       fanLCD = map(temp, tempMin, tempMax, 0, 100);  // speed of fan to display on LCD100
       analogWrite(fan, fanSpeed);  // spin the fan at the fanSpeed speed
   } 
   
   if(temp > tempMax) // if temp is higher than tempMax
     {        
     digitalWrite(led, HIGH);  // turn on led 
     } 
   else               // else turn of led
     {                    
     digitalWrite(led, LOW); 
     }
   
   lcd.print("TEMP: ");
   lcd.print(temp);      // display the temperature
   lcd.print("C ");
   lcd.setCursor(0,1);   // move cursor to next line
   lcd.print("FANS: ");
   lcd.print(fanLCD);    // display the fan speed
   lcd.print("%");
   delay(200);
   lcd.clear();  

   //current sensor
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
delay(2500); delay of 2.5 sec
} 
}

int readTemp() {  // get the temperature and convert it to celsius
  temp = analogRead(tempPin);
  return temp * 0.48828125;
}
