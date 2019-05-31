#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
#define pumpon1 3
#define pumpon2 4

int temp=0,i=0;
int led=13;
char str[15];
     
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
   pinMode(pumpon1, OUTPUT);
   pinMode(pumpon2, OUTPUT);

      Serial.print("GSM Control Home");
      Serial.print("   Automaton    ");
      delay(2000);
      Serial.print("System Ready");
      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  mySerial.println("AT+CMGF=1");
  delay(1000);
}


void loop()
{

  serialEvent();
  if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }

  }

// if (mySerial.available()>0)
//   Serial.write(mySerial.read());


void serialEvent() 
 {
  while(mySerial.available()) 
  {
    if(mySerial.find("#A."))
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      while(mySerial.available()) 
      {
      char inChar=mySerial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 
      } 
    }
   }
 }
 
void check()
{
   if(!(strncmp(str,"pump on",7)))
    {
      digitalWrite(pumpon1,HIGH);
      Serial.print("ON    ");
      delay(200);
    }  
   
   else if(!(strncmp(str,"pump off",6)))
    {
      digitalWrite(pumpon1, LOW); 
      Serial.print("OFF    ");
      delay(200);
    }
 
    }
 
