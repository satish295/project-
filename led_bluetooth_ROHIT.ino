
int fan = 3;
int light = 4;
int state;

void setup() {
    // sets the pins as outputs:
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
   
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);

    
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
     
    }   
    
    if (state == '0') {
        digitalWrite(3, LOW); 
       Serial.println("FAN OFF");
       delay(100);
        
        }
    

   else if (state == '1') {
        digitalWrite(3, HIGH);
       Serial.println("FAN ON");
       delay(100);
   }

   else if (state == '2') {
        digitalWrite(4,LOW);
       Serial.println("LIGHT OFF");
       delay(100);
   }
   else if (state == '3') {
        digitalWrite(4, HIGH);
       Serial.println("LIGHT ON");
       delay(100);
   }
   
   else
    {
        
       
          Serial.println("");
          delay(500);
         
        
    }
}
