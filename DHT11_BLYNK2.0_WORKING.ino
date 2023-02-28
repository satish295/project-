#define BLYNK_TEMPLATE_ID "TMPLvaLdjyGq"
#define BLYNK_DEVICE_NAME "Smart plant monitoring"
#define BLYNK_AUTH_TOKEN "aKrTrj53u0B6q0qmconQB-hf49audsfl"

#include <DallasTemperature.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

#include <DHT.h>

#define ONE_WIRE_BUS 14 // DS18B20 on arduino pin2 corresponds to D4 on physical board "D4 pin on the ndoemcu Module"
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;
float Fahrenheit=0;



char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "VIRUS";  // type your wifi name
char pass[] = "EXTC2021";  // type your wifi password

BlynkTimer timer;


#define DHTPIN 2 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V1, t);
    Blynk.virtualWrite(V2, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
}
void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0); // Celcius
   Fahrenheit = DS18B20.toFahrenheit(temp); // Fahrenheit
  Serial.println(temp);
  Serial.println(Fahrenheit);
  Blynk.virtualWrite(V3, temp); //virtual pin V3
  Blynk.virtualWrite(V4, Fahrenheit); //virtual pin V4
}

int sensor=0;
int output=0;

void sendTemps()
{
sensor=analogRead(A0);
output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
delay(1000);

Blynk.virtualWrite(V5,output);
delay(1000);
Serial.print("moisture = ");
Serial.print(output);
Serial.println("%");

}

WidgetLED led1(V6);

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


void setup()
{   
  
  Serial.begin(115200);
  

  Blynk.begin(auth, ssid, pass);
  dht.begin();
    DS18B20.begin();
  timer.setInterval(1000L, getSendData);
  timer.setInterval(100L, sendSensor);
   timer.setInterval(100L, sendTemps);
  timer.setInterval(1000L, blinkLedWidget);

  }

void loop()
{
  Blynk.run();
  timer.run();


 }
