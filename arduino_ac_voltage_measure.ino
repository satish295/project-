#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

int m=0;// initialise variable m
float n=0;//initialise variable n
int Rled = 5;
int Gled = 6;


void setup()
{
 lcd.init();
  lcd.clear();
   lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Over voltage");
  lcd.setCursor(0,1);
  lcd.print("Detection ");
  delay(300);
  
  pinMode(A0,INPUT); // set pin a0 as input pin
  Serial.begin(9600);// begin serial communication between arduino and pc
   pinMode(Rled, OUTPUT);
   pinMode(Gled, OUTPUT);
   digitalWrite(Rled, LOW);
   digitalWrite(Gled, LOW);
  
}

void loop()
{
  m=analogRead(A0);// read analog values from pin A0 across capacitor
   n=(m* .304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
  
   Serial.print("   analaog input  " ) ; // specify name to the corresponding value to be printed
   Serial.print(m); // print input analog value on serial monitor
   Serial.print("   ac voltage  ") ; // specify name to the corresponding value to be printed
   Serial.print(n); // prints the ac value on Serial monitor
   Serial.println();
   delay(100);
   if (n > 290 )
   {
    
    
    digitalWrite(Rled, HIGH);
    digitalWrite(Gled, LOW);
    lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Over voltage");
        lcd.setCursor(0,1);
       lcd.print(" Detect");
    delay(500);
    
    
    }
    else if( n>150 && n<260)
    {
      
    
        lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("supply connected");
        lcd.setCursor(0,1);
       lcd.print("......");
    digitalWrite(Gled, HIGH);
    digitalWrite(Rled, LOW);
    delay(300);
      
      }
      else 
      {
        lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("supply not");
        lcd.setCursor(0,1);
       lcd.print("connected");
        Serial.print("supply not connected");
            digitalWrite(Rled, LOW);
                digitalWrite(Gled, LOW);
        }

      

     
}
