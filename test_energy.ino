#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//#define BLYNK_TEMPLATE_ID "TMPL4RH9iGGH"
//#define BLYNK_TEMPLATE_NAME "IOT base Energy Meter"
//#define BLYNK_AUTH_TOKEN "HpIPJnsfBXS0FLRjR46jbgVBxArVEtWh"

//char AUTH[] = "-----------------"; //Auth code sent via Email

char AUTH[] = "HpIPJnsfBXS0FLRjR46jbgVBxArVEtWh"; //Auth code sent via Email
char WIFI_SSID[] = "VIRUS"; //Wifi name
char WIFI_PASS[] = "EXTC2021";  //Wifi Password

#define Relay1  D0 //GPIO 16
#define Relay2  D3 //GPIO 0

#define Switch1 10 //SD3
#define Switch2 9  //SD2


#define wifiLed D4 //GPIO 2

int load1, load2;
int wifiFlag = 1;

BlynkTimer timer;

void checkBlynkStatus() { // called every 3 seconds by SimpleTimer
  bool isconnected = Blynk.connected();
  if (isconnected == false) {wifiFlag = 1;
    digitalWrite(wifiLed, HIGH); //Turn off WiFi LED
  }
  if (isconnected == true) {
  if(wifiFlag==1){wifiFlag = 0;
  update_blynk();
  }  
    digitalWrite(wifiLed, LOW); //Turn on WiFi LED
  }
}

PZEM004Tv30 pzem(D7, D8);


void setup() {
Serial.begin(115200);
pinMode(Switch1, INPUT_PULLUP);
pinMode(Switch2, INPUT_PULLUP);


EEPROM.begin(512);
load1 = EEPROM.read(1);
load2 = EEPROM.read(2);

pinMode(Relay1, OUTPUT); 
pinMode(Relay2, OUTPUT); 


Relays();

pinMode(wifiLed, OUTPUT);

WiFi.begin(WIFI_SSID, WIFI_PASS);
timer.setInterval(3000L, checkBlynkStatus); // check if Blynk server is connected every 3 seconds
Blynk.config(AUTH);
delay(100);
lcd.init();
  lcd.backlight();
 lcd.clear();
lcd.setCursor(0,0);
 lcd.print("IOT Base");
 lcd.setCursor(0,1);
lcd.print("Energy Meter ");

}
void loop() {
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

if (WiFi.status() != WL_CONNECTED){
    //Serial.println("WiFi Not Connected");
  }
  else{
    //Serial.println("WiFi Connected");
    Blynk.run();
  }
 
if(wifiFlag==0){with_internet();}
           else{without_internet();}

 timer.run(); // Initiates SimpleTimer
 
}
BLYNK_WRITE(V0){
load1 = param.asInt();
Relays();
}

BLYNK_WRITE(V1){
load2 = param.asInt(); 
Relays();
}

void with_internet(){
     if(digitalRead(Switch1) == LOW){
      load1 = !load1;
      Relays(); 
      update_blynk();
      delay(300); 
    }
else if(digitalRead(Switch2) == LOW){
      load2 = !load2;
      Relays(); 
      update_blynk();
      delay(300);
    }
}
void without_internet(){
     if(digitalRead(Switch1) == LOW){
      load1 = !load1;
      Relays(); 
      delay(300); 
    }
else if(digitalRead(Switch2) == LOW){
      load2 = !load2;
      Relays(); 
      delay(300);
    }
}

void update_blynk(){
Blynk.virtualWrite(V0, load1);  
Blynk.virtualWrite(V1, load2);

}

void Relays(){
digitalWrite(Relay1, load1);  
digitalWrite(Relay2, load2);

write_eeprom();
}

void write_eeprom(){
EEPROM.write(1, load1);
EEPROM.write(2, load2);
EEPROM.commit(); 
}
