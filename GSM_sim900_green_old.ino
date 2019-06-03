#include <SoftwareSerial.h> 
SoftwareSerial gsmSerial(2,3);
String destinationNumber = "+917738041183";

void setup()
{
Serial.begin(4800);
gsmSerial.begin(4800);
gsmSerial.print("AT+CMGF=1\r");
delay(1000);
gsmSerial.println("AT + CMGS = \"" + destinationNumber +"\"");
delay(1000);
gsmSerial.print("Satish Lakhan");
delay(1000);
gsmSerial.write((char)26);
 delay(1000);
gsmSerial.println("AT+CLTS=1");
gsmSerial.println("AT+CCLK?");
}
void loop()
{}
