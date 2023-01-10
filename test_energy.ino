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
void setup() {
Serial.begin(115200);
timer.setInterval(1000L, blinkLedWidget);
}
void loop() {
 Blynk.run();
 timer.run();
 
float voltage = pzem.voltage();
if(voltage != NAN){
Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
} else {
Serial.println("Error reading voltage");
}
float current = pzem.current();
if(current != NAN){
Serial.print("Current: "); Serial.print(current); Serial.println("A");
} else {
Serial.println("Error reading current");
}
float power = pzem.power();
if(current != NAN){
Serial.print("Power: "); Serial.print(power); Serial.println("W");
} else {
Serial.println("Error reading power");
}
float energy = pzem.energy();
if(current != NAN){
Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
} else {
Serial.println("Error reading energy");
}
float frequency = pzem.frequency();
if(current != NAN){
Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
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
