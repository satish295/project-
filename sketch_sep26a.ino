#include "UbidotsESPMQTT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define TOKEN "*********************************" // Your Ubidots TOKEN
#define WIFINAME "************" //Your SSID
#define WIFIPASS "*************" // Your Wifi Pass
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
#define inSensor 14
#define outSensor 12
 
#define relay 0
 
int inStatus;
int outStatus;
 
int countin = 0;
int countout = 0;
 
int in;
int out;
int now;
 
Ubidots client(TOKEN);
 
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
 
 
void setup()
{
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
 
  pinMode(inSensor, INPUT);
  pinMode(outSensor, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
 
  Serial.println("Visitor Counter Demo");
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.print("Visitor");
  display.setCursor(20, 40);
  display.print("Counter");
  display.display();
  delay(3000);
 
 
}
 
void loop()
{
  if (!client.connected())
  {
    client.reconnect();
  }
 
  inStatus =  digitalRead(inSensor);
  outStatus = digitalRead(outSensor);
  if (inStatus == 0)
  {
    in = countin++;
  }
 
  if (outStatus == 0)
  {
    out = countout++;
  }
 
  now = in - out;
 
  if (now <= 0)
  {
    digitalWrite(relay, HIGH);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 15);
    display.print("No Visitor");
    display.setCursor(5, 40);
    display.print("Light Off");
    display.display();
    Serial.println("No Visitors! Light Off");
    delay(500);
  }
  else
  {
    digitalWrite(relay, LOW);
 
    display.clearDisplay();
    display.setTextColor(WHITE);
 
    display.setTextSize(1);
    display.setCursor(15, 0);
    display.print("Current Visitor");
    display.setTextSize(2);
    display.setCursor(50, 15);
    display.print(now);
 
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print("IN: ");
    display.print(in);
 
    display.setTextSize(1);
    display.setCursor(70, 40);
    display.print("OUT: ");
    display.print(out);
 
    display.display();
 
    Serial.print("Current Visitor: ");
    Serial.println(now);
    Serial.print("IN: ");
    Serial.println(in);
    Serial.print("OUT: ");
    Serial.println(out);
    delay(500);
  }
  int relaystatus = digitalRead(relay);
  client.add("in", in);
  client.add("out", out);
  client.add("now", now);
  client.add("Light Status", relaystatus);
  client.ubidotsPublish("ESP8266");
  client.loop();
  Serial.println();
  delay(100);
}
