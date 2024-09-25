#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "admin";//Replace with your network SSID
const char* password = "12345678";//Replace with your network password

ESP8266WebServer server(80);

String page = "";
char input[12];
int count = 0;


int a;
int p1=0,p2=0,p3=0,p4=0;
int c1=0,c2=0,c3=0,c4=0;

double total = 0;
int count_prod = 0;
void setup()
{
  pinMode(D3,INPUT_PULLUP);
  pinMode(D4,OUTPUT);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO       ");
  lcd.setCursor(0, 1);
  lcd.print("   SMART CART       ");

  delay(2000);

  lcd.clear();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting...  ");
  }
  Serial.print(WiFi.localIP());
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print(" PLZ ADD ITEMS     ");
  lcd.setCursor(0, 1);
  lcd.print("    TO CART          ");

server.on("/", []()
  {
    page = "<html><head><title>E Cart using IoT</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Shopping Cart using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Biscuit</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>";
    page += "<tr><td>Soap</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr><tr><td>Rice(1KG)</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td>";
    page += "</tr><tr><td>Tea(50g)</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr><tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th>";
    page += "</tr></table><br><input type=\"button\" name=\"Pay Now\" value=\"Pay Now\" style=\"width: 200px;height: 50px\"></center></body></html>",(page);
  });
  server.begin();
}
void loop()
{
  int a = digitalRead(D4);
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12)
    {
      if ((strncmp(input, "0B00291F5B66", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Biscuit Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):35.00      ");
        p1++;
        digitalWrite(D4,HIGH);
        delay(2000);
        total = total + 35.00;
        count_prod++;
        digitalWrite(D4,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "0B00291F5B66", 12) == 0) && (a == 0))
      {
        if(p1>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Biscuit Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        p1--;
        total = total - 35.00;
        count_prod--;
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        digitalWrite(D4,LOW);
        lcd.clear();
        }
      }
      else if ((strncmp(input, "0B002920D0D2", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Soap Added          ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):38.00         ");
        total = total + 38.00;
        digitalWrite(D4,HIGH);
        delay(2000);
        p2++;
        count_prod++;
        digitalWrite(D4,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "0B002920D0D2", 12) == 0) && (a == 0))
      {
         if(p2>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Soap Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        p2--;
        total = total - 38.00;
        count_prod--;
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
      }
      else if ((strncmp(input, "0B002948A8C2", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Rice(1KG) Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):55.00      ");
        total = total + 55.00;
        digitalWrite(D4,HIGH);
        delay(2000);
        count_prod++;
        p3++;
        lcd.clear();
        digitalWrite(D4,LOW);
      }
      else if ((strncmp(input, "0B002948A8C2", 12) == 0) && (a==0))
      {
        if(p3>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Rice(1KG) Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        total = total - 55.00;
        p3--;
        count_prod--;
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
      }
      else if ((strncmp(input, "0B00283BFEE6", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Tea(50g) Added            ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):45.00        ");
        total = total + 45.00;
        count_prod++;
        digitalWrite(D4,HIGH);
        p4++;
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
      }
      else if ((strncmp(input, "0B00283BFEE6", 12) == 0) && (a == 0))
      {
        if(p4>0)
        {
        lcd.clear();
        total = total - 45.00;
        lcd.setCursor(0, 0);
        count_prod--;
        p4--;
        lcd.print("Tea(50g) Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
      }
      else if (strncmp(input, "0B00292BADA4", 12) == 0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Prod:");
        lcd.setCursor(11, 0);
        lcd.print(count_prod);
        lcd.setCursor(0, 1);
        lcd.print("Price:");
        lcd.setCursor(6, 1);
        lcd.print(total);
        
        digitalWrite(D4,HIGH);
        delay(2000);

        lcd.clear();
        digitalWrite(D5,LOW);
        lcd.setCursor(0, 0);
        lcd.print("   Thank you        ");
        lcd.setCursor(0, 1);
        lcd.print("  for Shopping        ");
        digitalWrite(D4,LOW);
      }
    }
    c1=p1*35.00;
    c2=p2*38.00;
    c3=p3*55.00;
    c4=p4*45.00;
  }
server.handleClient();
}
