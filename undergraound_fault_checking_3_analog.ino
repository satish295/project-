
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int distance;

int sensorPin1 = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;    // select the input pin for the potentiometer
int sensorPin3 = A2;    // select the input pin for the potentiometer

int ledPin = 13;      // select the pin for the LED
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor

byte symbol[8] = {
        B00000,
        B00100,
        B00100,
        B00100,
        B11111,
        B01110,
        B00100,
        B00000
        };

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  lcd.createChar(1, symbol);
 lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
lcd.clear();
lcd.setCursor(0, 0); // set the cursor to column 0, line 2
lcd.print("Welcome! Cable");
lcd.setCursor(0, 1); // set the cursor to column 0, line 2
lcd.print("Fault  Detection");
delay(2000);
lcd.clear();

}

void loop() {
  // read the value from the sensor:
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  lcd.setCursor(1,0);
lcd.print("R");
lcd.write(1);  

lcd.setCursor(7,0);
lcd.print("Y");
lcd.write(1); 

lcd.setCursor(13,0);
lcd.print("B");
lcd.write(1); 


  // turn the ledPin on
  Serial.println(sensorValue1);
    Serial.println(sensorValue2);
  Serial.println(sensorValue3);

  delay(1000);

  if(sensorValue1>985)
{
    lcd.setCursor(1,1);

  lcd.print("2"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
 else if(sensorValue1>940 && sensorValue1<965)
{
      lcd.setCursor(1,1);

  lcd.print("4"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
 else if(sensorValue1>900 && sensorValue1<939 )
{
      lcd.setCursor(1,1);

  lcd.print("6"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
else
{
  lcd.setCursor(1,1);
  lcd.print("NF");
  }

  

 if(sensorValue2>760)
{
  lcd.setCursor(7,1);

  lcd.print("2"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
 else if(sensorValue2>720 && sensorValue2< 750)
{
   lcd.setCursor(7,1);

  lcd.print("4"); 
  lcd.print("KM");
 //Serial.println(distance);
 }

 else if(sensorValue2>670 && sensorValue2< 710)
{
    lcd.setCursor(7,1);

  lcd.print("6"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
else
{
    lcd.setCursor(7,1);

  lcd.print("NF");
  }

  

   if(sensorValue3>890)
{
    lcd.setCursor(13,1);

  lcd.print("2"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
 else if(sensorValue3>850 && sensorValue3<885)
{
      lcd.setCursor(13,1);

  lcd.print("4"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
 else if(sensorValue3>760 && sensorValue3 < 840)
{
 
      lcd.setCursor(13,1);
  lcd.print("6"); 
  lcd.print("KM");
 //Serial.println(distance);
 }
else
{
      lcd.setCursor(13,1);

  lcd.print(" NF ");
  }



  }
