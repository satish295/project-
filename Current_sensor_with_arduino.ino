
// include the library code:
#include <LiquidCrystal.h> //library for LCD
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
 
//Measuring Current Using ACS712
 
const int analogIn = 0; //Connect current sensor with A0 of Arduino
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500;
double Voltage = 0; //voltage measuring
double Amps = 0;// Current measuring
 
void setup() {
  //baud rate
  Serial.begin(9600);//baud rate at which arduino communicates with Laptop/PC
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);  //LCD order
  // Print a message to the LCD.
  lcd.setCursor(1,1);//Setting cursor on LCD
  lcd.print("www.TheEngineering");//Prints on the LCD
  lcd.setCursor(4,2);
  lcd.print("Projects.com");
  delay(3000);//time delay for 3 sec
  lcd.clear();//clearing the LCD display
  lcd.display();//Turning on the display again
  lcd.setCursor(1,0);//setting LCD cursor
  lcd.print("Reading Values from");//prints on LCD
  lcd.setCursor(1,1);
  lcd.print("DC Current Sensor");
  lcd.setCursor(5,2);
  lcd.print("ACS 712");
  delay(2000);//delay for 2 sec
}
 
void loop() //method to run the source code repeatedly
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
