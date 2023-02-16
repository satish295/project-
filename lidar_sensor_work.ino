#include <SoftwareSerial.h> //header file of software serial port
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

SoftwareSerial Serial1(2,3); //define software serial port name as Serial1 and define pin2 as RX and pin3

//int enA = 3;
int in1 = 4;
int in2 = 5;

/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and
directly use Serial1 serial port*/
int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
float temprature;
int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package

void setup() {

 Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
 Serial1.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino
 lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("LIDAR OBSTACLE");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("DETECTION");

  //pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

}
void loop() {
  //Serial.print("hii");
  Serial.print(Serial1.read());
 if (Serial1.available()) { //check if serial port has data input
 if(Serial1.read() == HEADER) { //assess data package frame header 0x59
 uart[0]=HEADER;
 if (Serial1.read() == HEADER) { //assess data package frame header 0x59
 uart[1] = HEADER;
 for (i = 2; i < 9; i++) { //save data in array
 uart[i] = Serial1.read();
 }
 check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
 if (uart[8] == (check & 0xff)){ //verify the received data as per protocol
  dist = uart[2] + uart[3] * 256; //calculate distance value
  strength = uart[4] + uart[5] * 256; //calculate signal strength value
  temprature = uart[6] + uart[7] *256;//calculate chip temprature
  temprature = temprature/8 - 256;
  Serial.print("dist = ");
  Serial.print(dist); //output measure distance value of LiDAR

  Serial.print('\t');

  Serial.print("strength = ");
  Serial.print(strength); //output signal strength value
  Serial.print("\t Chip Temprature = ");
  Serial.print(temprature);
  Serial.println(" celcius degree"); //output chip temperature of Lidar
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Distance");
  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  lcd.print(dist);
  directionControl();
 if(dist<200)
 {
  Serial.print("object detected");

    lcd.clear();
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Obstacle Detect");
  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  lcd.print("Motor Stop");

delay(10000);
  }
  delay(1000);
 }
 }
 }
 }
}
void directionControl() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	//analogWrite(enA, 255);(
	//analogWrite(enB, 255);

	// Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	delay(2000);
	
	// Now change motor directions
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	delay(2000);
}


void motorstop()
{
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);

}