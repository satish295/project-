
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int M1 = 8;
int M11 = 9;
int M2 = 10;
int M22 = 11;
int threshold = 750;
void setup(){
  pinMode (sensor1, INPUT);
  pinMode (sensor2, INPUT);
  pinMode (sensor3, INPUT);
  pinMode (sensor4, INPUT);
  pinMode (M1, OUTPUT);
   pinMode (M11, OUTPUT);
    pinMode (M2, OUTPUT);
     pinMode (M22, OUTPUT);

  Serial.begin(9600);
  
}
void loop(){
 int analogValue1 = analogRead(sensor1);
int analogValue2 = analogRead(sensor2);
int analogValue3 = analogRead(sensor3);
int analogValue4 = analogRead(sensor4);
Serial.println(analogValue1);
Serial.println(analogValue2);
Serial.println(analogValue3);
Serial.println(analogValue4);
delay(1000);
{

if (analogValue1 > threshold && analogValue2 < threshold && analogValue3 < threshold && analogValue4 < threshold) {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
    Serial.print("Sensor 1 "); // RIGHT DIRECTION BOTTOM 
  
  delay(300);
  digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
    
  }
else if (analogValue1 < threshold && analogValue2 > threshold && analogValue3 < threshold && analogValue4 < threshold) {
    digitalWrite(M1, LOW);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);

    Serial.print("Sensor 2 "); //LEFT DIRECTION BOTTOM
  
  delay(300);
  digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
    
  } 

else if (analogValue1 < threshold && analogValue2 < threshold && analogValue3 > threshold && analogValue4 < threshold) {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, LOW);
     Serial.print("Sensor 3 ");  // 
   
  delay(10);
//  digitalWrite(M1, HIGH);
//    digitalWrite(M11, HIGH);
//    digitalWrite(M2, HIGH);
//    digitalWrite(M22, HIGH);
  } 
//  else {
//    digitalWrite(led3, LOW);
//}
else if (analogValue1 < threshold && analogValue2 < threshold && analogValue3 < threshold && analogValue4 > threshold) {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M22, HIGH);
   
    Serial.print("Sensor 4 "); 
       delay(10);
  digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
  } 
else {
    digitalWrite(M1, HIGH);
    digitalWrite(M11, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M22, HIGH);
    Serial.print("sensor not detect");
  delay(50);
}
}
}
