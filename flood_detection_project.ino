#include<XBee.h>
#include<SoftwareSerial.h>
SoftwareSerial XBee(2,3);

int user1 = 11;
int user2 = 12;
int motorsw = 8;
int motor = 10;
int buzzer = 9;
void setup()
{
  
  Serial.begin(9600);
  pinMode(user1, INPUT_PULLUP);
  pinMode(user2, INPUT_PULLUP);
  
  XBee.begin(9600);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(10,OUTPUT);
  pinMode(8, INPUT_PULLUP);
  
 digitalWrite(motor,HIGH);
  }
  void loop()
{
   int buttonState1 = digitalRead(user1);
   int buttonState2 = digitalRead(user2);
    int buttonState3 = digitalRead(motorsw);
   


    int sensorVal1 = digitalRead(5);
     int sensorVal2 = digitalRead(6);
      int sensorVal3 = digitalRead(7);
  //print out the value of the pushbutton
  Serial.println(sensorVal1);
  Serial.println(sensorVal2);
  Serial.println(sensorVal3);

  if( (buttonState1 == LOW && buttonState2 == HIGH) || (buttonState1 == HIGH && buttonState2 == LOW ))
  {
    if (buttonState3 == LOW)
    {
      XBee.write('G');
      digitalWrite(motor,LOW); 
      }
 else 
   {
     
      digitalWrite(motor,HIGH); 
      }
  }
 else if (buttonState1 == LOW && buttonState2 == LOW)
 {
  
  XBee.write('A');
  delay(2000);
  digitalWrite(buzzer,LOW); 
 delay(2000);
  }
    
    
  
}

