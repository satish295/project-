int m;// initialise variable m
float n;//initialise variable n

void setup()
{
  pinMode(A0,INPUT); // set pin a0 as input pin
  Serial.begin(9600);// begin serial communication between arduino and pc
}

void loop()
{
  m=analogRead(A0);// read analog values from pin A0 across capacitor
   n=(m* .304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
  
   Serial.print("   analaog input  " ) ; // specify name to the corresponding value to be printed
   Serial.print(m) ; // print input analog value on serial monitor
   Serial.print("   ac voltage  ") ; // specify name to the corresponding value to be printed
   Serial.print(n) ; // prints the ac value on Serial monitor
   Serial.println();
}
