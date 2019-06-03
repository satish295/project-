int led = 13;unsigned char Buff[250];unsigned char BuffIndex;void setup()
{pinMode(led, OUTPUT);Serial.begin(9600);Serial.println("GSM DTMF Tutorial, Valetron Systems @www.raviyp.com ");Serial.println("Any tech queries to be posted to www.embeddedadvice.com ");delay(3000);Serial.print("ATS0=2\r\n");delay(3000);Serial.print("AT+DDET=1\r\n");delay(3000);memset(Buff, '\0', 250);// Initialize the string
BuffIndex=5;}
void loop()
{while(1)
{if(Serial.available()>0)
{Buff[BuffIndex] = Serial.read();if( (Buff[BuffIndex-5] == 'D') &&(Buff[BuffIndex-4] == 'T') && (Buff[BuffIndex-3] == 'M') &&(Buff[BuffIndex-2] == 'F') && (Buff[BuffIndex-1] == ':') && (Buff[BuffIndex] == '1'))
{Serial.println("Button 1 Pressed, LED Turned ON");digitalWrite(led, HIGH);}
if( (Buff[BuffIndex-5] == 'D') &&(Buff[BuffIndex-4] == 'T') && (Buff[BuffIndex-3] == 'M') &&(Buff[BuffIndex-2] == 'F') && (Buff[BuffIndex-1] == ':') && (Buff[BuffIndex] == '0'))
{Serial.println("Button 0 Pressed, LED Turned OFF");digitalWrite(led, LOW);}
BuffIndex++;if(BuffIndex>250)
{BuffIndex=5;}}}}
