//DHT11 And NodeMCU With Blynk
//My GitHub https://github.com/manoranjan2050
//My Hackster.io https://www.hackster.io/Manoranjan2050
//This Video Link https://youtu.be/0dbws1i2GoE
#define BLYNK_TEMPLATE_ID "TMPLEgWUyyND"
#define BLYNK_DEVICE_NAME "Building automation"
#define BLYNK_AUTH_TOKEN "utN9ZtqeN92al_TZ2Wvb7NaYOmvoYT5N"
#define BLYNK_PRINT Serial
 const int xPin = A0;    //x-axis of the Accelerometer 

//BlynkTimer timer;  
 #include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "utN9ZtqeN92al_TZ2Wvb7NaYOmvoYT5N";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "VIRUS";
char pass[] = "EXTC2021";
 
#define DHTPIN D4          // D3
 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 const int pushButton = D5;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
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
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
     Serial.println(t);  

}

  int flag=0;  
 void notifyOnFire()  
 {  
  int isButtonPressed = digitalRead(D6);  
  if (isButtonPressed==1 && flag==0) {  
   Serial.println("Fire DETECTED");  
  // Blynk.notify("Alert : Fire detected");  
   flag=1;  
  }  
  else if (isButtonPressed==0)  
  {  
   flag=0;  
  }  
 }  

void setup()
{
  // Debug console
  Serial.begin(9600);
 lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("IOT Building");
  lcd.setCursor(0,1);
  lcd.print("Automation");
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
 
  dht.begin();
   pinMode(pushButton, INPUT);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
   pinMode(D1,INPUT_PULLUP);  
 timer.setInterval(1000L,notifyOnFire);   

}
 
void loop()
{
   int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  delay(1000);
  Blynk.run();
 timer.run();
  if (buttonState == HIGH) {
   //digitalWrite(13, LOW);
     Blynk.virtualWrite(V2, LOW);
     Serial.print("MQ2 high");

 } else {
  //  digitalWrite(13, HIGH);
     Blynk.virtualWrite(V2, HIGH);

  }
int x = analogRead(xPin);
 delay(100);

  Serial.print("X-axis : ");
  Serial.println(x);
     Blynk.virtualWrite(V3, x);
if (x > 500)
{
    Blynk.notify("Alert : Earth quick detected");  
    lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("Earth Quick detect");

    

  }

  

}
