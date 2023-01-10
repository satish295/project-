#define BLYNK_TEMPLATE_ID "TMPLEgWUyyND"
#define BLYNK_DEVICE_NAME "Building automation"
#define BLYNK_AUTH_TOKEN "utN9ZtqeN92al_TZ2Wvb7NaYOmvoYT5N"
#define BLYNK_PRINT Serial

//BlynkTimer timer;  
 #include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

BlynkTimer timer; 

PZEM004Tv30 pzem(D7, D8);

WidgetLED led1(V1);
// V1 LED Widget is blinking
void blinkLedWidget()  // function for switching off and on LED
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }
}

WidgetLED led2(V2);

void blinkLedWidget1()  // function for switching off and on LED
{
  if (led2.getValue()) {
    led2.off();
    Serial.println("LED on V2: off");
  } else {
    led2.on();
    Serial.println("LED on V2: on");
  }
}

void setup() {
Serial.begin(115200);
 lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("IOT Base");
  lcd.setCursor(0,1);
  lcd.print("Energy Meter");
 
timer.setInterval(1000L, blinkLedWidget);
 timer.setInterval(1000L, blinkLedWidget1);
}
void loop() {
 Blynk.run();
 timer.run();
 lcd.clear();
 lcd.setCursor(0,0);
  lcd.print("V:");
 lcd.setCursor(0,8);
  lcd.print("I:");
 lcd.setCursor(1,0);
  lcd.print("W:")
   lcd.setCursor(1,8);
  lcd.print("KWh:")
 
float voltage = pzem.voltage();
if(voltage != NAN){
Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
 
 Blynk.virtualWrite(V3, voltage);
} else {
Serial.println("Error reading voltage");
}
float current = pzem.current();
if(current != NAN){
Serial.print("Current: "); Serial.print(current); Serial.println("A");
 Blynk.virtualWrite(V4, current);
} else {
Serial.println("Error reading current");
}
float power = pzem.power();
if(current != NAN){
Serial.print("Power: "); Serial.print(power); Serial.println("W");
 Blynk.virtualWrite(V5, power);
} else {
Serial.println("Error reading power");
}
float energy = pzem.energy();
if(current != NAN){
Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
 Blynk.virtualWrite(V6, energy);
} else {
Serial.println("Error reading energy");
}
float frequency = pzem.frequency();
if(current != NAN){
Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
  Blynk.virtualWrite(V7, frequency);
} else {
Serial.println("Error reading frequency");
}
float pf = pzem.pf();
if(current != NAN){
Serial.print("PF: "); Serial.println(pf);
} else {
Serial.println("Error reading power factor");
}
Serial.println();
delay(2000);
}
