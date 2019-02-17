/*
This is free to use :-) (I don't know why but i love writing this line)

Hello everbody i am satinder singh, i am acomputer engineering student at Army Institute of Technology in pune
This is my code for identifying basic red,green and blue color and connecting this with a servo to project this physically

if you don't have knowledge about processing and want to learn about it i would recommend you Daniel shiffmans channel "The Coding Train"

The link to youtube video for this project is : 

the components required are
arduino uno
jumper wires
servo
motor shield(can work without it also)
laptop with processing and arduino installed

just connect VCC,GROUND to GND and 5V of the arduino
and connect the third pin of servo to any digital pin


make sure you install the video library before use
This is the processing code
You can check the other file for arduino code
*/

import processing.video.*;           //importing the video library
import processing.serial.*;          //importing the Serial library
Capture video;                       //making a object video of class Capture
Serial x;                           //making a object x of class Serial

 
 
//capture event is  a built in function that runs whenever there is a frame avialable
void captureEvent(Capture video)    
{
video.read();                     //whenever the frame is available we read the frame
}

//void setup -> this function runs once
void setup()  
{
  
  x=new Serial(this,"COM3",9600);   // i set the COM number and the baud rate for the communication between arduino and processing serially
  size(640,480);                    //this is the size of the window
  video=new Capture(this,640,480);  //setting information about the video
  video.start();                    //starting the video
}

//void draw->this function runs infinitely number of times until the program is closed
void draw()
{
  int k=0,l=0,m=0;
  loadPixels();          //loading the pixels of the screen
  video.loadPixels();    //loading the pixels of the video

  image(video,0,0);      //drawing one frame of video on the screen
  rectMode(CENTER);      //setting the starting drawing point for the rectangle to be the point where the diagonals of the rectangle cross each other
  stroke(255,0,255);     //setting outline color
  strokeWeight(5);       //setting thickness of the outline
  noFill();              //no color fill in the shape
  rect(width/2,height/2,100,100);   //drawing a rectangle taking reference point to be width/2 and height/2 and length and breadth of the rectangle to be 100 by 100 pixels
   stroke(0);                       //setting color of line to be black
   //rect(width/2-50,height/2-50,10,10);
  for(int x=(width/2-50);x<(width/2+50);x++)  //starting a loop from begining of the ractangle to end(width wise)
  {
  for(int y=(height/2-50);y<(height/2+50);y++) //starting loop from begining of the rectangle to end(height wise)
  {
   int loc=x+y*video.width;                    //as the pixels on the screen are in the form of a array so to refer to the pixels in the format of coordinate sytem i do this
                                               //(for more information refer to daniel shieffman tutorials on youtube channel name ->coding train)
   color currentColor=video.pixels[loc];       //declaing a variable of type current color which contains the color of the specific pixel
   float r=red(currentColor);                  //obtaining the red value of that current color
   float g=green(currentColor);                //obtaining the green value of that current color
   float b=blue(currentColor);                 //obtaining the blue value of that current color
   float h=dist(r,g,b,255,0,0);                //finding distance between current colors r,g,b values and red color
   float i=dist(r,g,b,0,255,0);                 //finding distance between current colors r,g,b values and green color
   float j=dist(r,g,b,0,0,255);               //finding distance between current colors r,g,b values and blue color
   
   
   if(((h<i)&&(h<j)))             //checking if red color is closest to the obtained color from the screen                
   {
   k++;
   }
    if(((i<h)&&(i<j)))            //checking if green color is closest to the obtained color from the screen
   {
   l++;
   }
    if(((j<i)&&(j<h)))           //checking if blue color is closest to the obtained color from the screen
   {
   m++;
   }
   }
   }
  if((k>l)&&(k>m))             //if the quantity of pixels whose red value is closest to red color is maximum then color is red
  {fill(225,30,30);            //setting fill color red
  strokeWeight(3);              //setting line thickness  
  textSize(40);                 //setting text size
  text("the color is red",50,40);      //text and its starting point 
  x.write('1');                        //sending value 1 throught serial port
  delay(1000);
}
    if((l>k)&&(l>m))            //if the quantity of pixels whose green value is closest to green color is maximum then color is green
  {fill(0,255,30);              //setting fill color green
  strokeWeight(3);              //setting line thickness
  textSize(40);                 //setting text size
  text("the color is green",50,40);  //text and its starting point 
x.write('2');                        //sending value 2 throught serial port
delay(1000);
}
    if((m>k)&&(m>l))             //if the quantity of pixels whose blue value is closest to blue color is maximum then color is blue
  {fill(0,30,255);                //setting fill color blue
  strokeWeight(3);                //setting line thickness
  textSize(40);                   //setting text size
  text("the color is blue",50,40);  //text and its starting point
x.write('3');                        //sending value 3 throught serial port
delay(1000);
}
}