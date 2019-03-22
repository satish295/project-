#include "math.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> // Arduino IDE <1.6.6
#include <PZEM004T.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
PZEM004T pzem(10,11);  // (RX,TX) connect to TX,RX of PZEM


IPAddress ip(192,168,1,1);



void setup() {


  Serial.begin(9600);


  pzem.setAddress(ip);


  pinMode(9, OUTPUT);
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

}

void loop(){


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


  Serial.print(p);Serial.print("W; ");
  lcd.setCursor(9,1);
  lcd.print("W= ");
  lcd.setCursor(11,1);
  lcd.print(p);




  float e = pzem.energy(ip);

  Serial.print("PF= ");Serial.print((p)/(v*i));

  lcd.setCursor(0,1);
  lcd.print("PF=");
  lcd.setCursor(3,1);
  lcd.print((p)/(v*i));

  
  Serial.println();
delay(2000);


 float Cap = ((((i)*sqrt(1-(((p)/(v*i))*((p)/(v*i)))))/(v*314))*1000000);

 float PF = ((p)/(v*i));

  Serial.print(Cap);Serial.print("uF ");

  Serial.print("PF= ");Serial.print((p)/(v*i));

 if (PF > 0.99){ 
      lcd.init(); 
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("Resistive Load");
      lcd.setCursor(0,1);
      lcd.print("No Cap. Needed");

  }
  
  else  if (PF < 0.99){ 

  Serial.println();
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Cap. Should Be =");
  lcd.setCursor(3,1);
  lcd.print(Cap);
  lcd.setCursor(8,1);
  lcd.print("uF");

  }

  if (i == 0.00){ 
      lcd.init();
      lcd.clear(); 
      lcd.backlight();
      lcd.setCursor(4,0);
      lcd.print("No Load");
       
  }
}
