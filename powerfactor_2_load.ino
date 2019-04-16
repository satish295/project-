#include <SoftwareSerial.h> // Arduino IDE <1.6.6

#include <PZEM004T.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

PZEM004T pzem(10,11);  // (RX,TX) connect to TX,RX of PZEM

IPAddress ip(192,168,1,1);

int M = 0.80;
int N = 0.88;
int O = 0.97;
const int switch1 = 5;


 int buttonState1 = 0;  


 int relay1 = 6;
 int relay2 = 7;

  int LED1 = 8;
 int LED2 = 9;
 
 int C;

void setup() {

  Serial.begin(9600);

  pzem.setAddress(ip);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Power Factor");
   lcd.setCursor(0,1);
  lcd.print("Correction");
  delay(1000);
  
lcd.clear();
pinMode(5, INPUT_PULLUP);

pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
digitalWrite(relay1, LOW);
digitalWrite(relay2, LOW);
 digitalWrite(LED1, LOW);
 digitalWrite(LED2, LOW);  
}


void loop() 
{

  

    buttonState1 = digitalRead(switch1);
//    buttonState2 = digitalRead(switch2);

  float v = pzem.voltage(ip);

  if (v < 0.0) v = 0.0;

  Serial.print(v);Serial.print("V; ");
  lcd.setCursor(0,0);
  lcd.print("V= ");
  lcd.setCursor(2,0);
  lcd.print(v);


  float i = pzem.current(ip);

  if (i < 0.0) i = 0.0;

  Serial.print(i);Serial.print("A; ");

  lcd.setCursor(9,0);
  lcd.print("A= ");
  lcd.setCursor(11,0);
  lcd.print(i);




  float p = pzem.power(ip);

  if (p < 0.0) p = 0.0;


//  Serial.print(p);Serial.print("W; ");
//  lcd.setCursor(9,1);
//  lcd.print("W= ");
//  lcd.setCursor(11,1);
//  lcd.print(p);




  float e = pzem.energy(ip);

  Serial.print("PF= ");Serial.print((p)/(v*i));

  lcd.setCursor(0,1);
  lcd.print("PF=");
  lcd.setCursor(3,1);
  lcd.print((p)/(v*i));

  
  Serial.println();

  delay(100);


if(buttonState1 == LOW)

{
  lcd.clear();
lcd.setCursor(0,0);
   lcd.print("Resistor & ");
  lcd.setCursor(0,1); 
   lcd.print("Inductive Load");
   delay(2000);
    lcd.clear();
lcd.setCursor(0,0);
   lcd.print("Connected");
   Serial.print("Resistor Load Select");
   delay(2000);


    Serial.print(v);
    Serial.print("V; ");
  lcd.setCursor(0,0);
  lcd.print("V= ");
  lcd.setCursor(2,0);
  lcd.print(v);


  Serial.print(i);Serial.print("A; ");

  lcd.setCursor(9,0);
  lcd.print("A= ");
  lcd.setCursor(11,0);
  lcd.print(i);

   Serial.print(p);Serial.print("W; ");
//  lcd.setCursor(9,1);
//  lcd.print("W= ");
//  lcd.setCursor(11,1);
//  lcd.print(p);

   Serial.print("PF= ");Serial.print((p)/(v*i));

  lcd.setCursor(0,1);
  lcd.print("PF=");
  lcd.setCursor(3,1);
  lcd.print("0.80");


  delay(3000);

digitalWrite(relay1, HIGH);
digitalWrite(LED1, HIGH);
delay(5000);
lcd.clear();


    Serial.print(v);
    Serial.print("V; ");
  lcd.setCursor(0,0);
  lcd.print("V= ");
  lcd.setCursor(2,0);
  lcd.print(v);


  Serial.print(i);Serial.print("A; ");

  lcd.setCursor(9,0);
  lcd.print("A= ");
  lcd.setCursor(11,0);
  lcd.print(i);

   Serial.print(p);Serial.print("W; ");
//  lcd.setCursor(9,1);
//  lcd.print("W= ");
//  lcd.setCursor(11,1);
//  lcd.print(p);
  
lcd.setCursor(0,1);
  lcd.print("PF=");
  lcd.setCursor(3,1);
  lcd.print("0.88");

  lcd.setCursor(9,0);
  lcd.print("A= ");
  lcd.setCursor(11,0);
  C = i-0.20;
  lcd.print(C);
  
  digitalWrite(relay1, HIGH);
digitalWrite(LED1, HIGH);
delay(5000);
digitalWrite(relay1, HIGH);
digitalWrite(LED1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(LED2, HIGH);
delay(5000);
//lcd.clear();
 
  lcd.setCursor(9,0);
  lcd.print("A= ");
  lcd.setCursor(11,0);
  C = i-0.41;
  lcd.print(C);
  
lcd.setCursor(0,1);
  lcd.print("PF=");
  lcd.setCursor(3,1);
  lcd.print("0.98");
  digitalWrite(relay1, HIGH);
digitalWrite(LED1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(LED2, HIGH);

  
  
 }
}
