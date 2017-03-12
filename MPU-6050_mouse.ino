/* Code to control the mouse pointer with the movement of the head
 * and assisted click.
 * Change the values at vx and vy (+300 and -100 in my case) 
 * setting them with the TEST code.
 * 
 * Gabry295
*/

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy,clik=0,clik1=0;/*, vxx,vy;*/
const int buttonPin = 5;     // the number of the pushbutton pin
const int button1Pin=6;
//const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;
int button1State=0;
void setup() {
  Serial.begin(36000);
  Wire.begin();
   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   
  pinMode(buttonPin, INPUT);
  pinMode(button1Pin,INPUT);
   vx=0;
   vy=0;
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
    }
}

void loop() {
  
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
/*vxx=vx-gx-310;
  vyy=vy-gz+26;*/
  vx =-gx-310; //(gy-vxx-200);//+7000)/10;  // "+300" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
  vy =-gz+26;// -(gz+vyy+700);//-4000)/10; // same here about "-100"

/* if(vxx<100&&vxx>-100)
  { vx=0;
    }
    if(vyy<100&&vyy>-100)
    {vy=0;}*/

  Serial.print(vx/800);
  Serial.print(",");
  Serial.print(vy/500);  
  Serial.print(",");
  /*
  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  
  Serial.print(" ");
  Serial.print(az);
  
  Serial.print(" ");
  Serial.print(gx);
  
  Serial.print(" ");
  Serial.print(gy);
  
  Serial.print(" ");
  Serial.print(gz);

   Serial.print(" ");
  Serial.print(vx);
    Serial.print(" ");
  Serial.println(vy);
*/

 buttonState = digitalRead(buttonPin);
 button1State = digitalRead(button1Pin);
 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  // if (millis()-cliktime>debound||(clik==0&&buttonState==LOW)) 
   //{
    
//    cliktime=millis();

// LEFT CLICK
    if (clik==0&&buttonState == LOW) {
   clik=1;
    // turn LED on:
    Serial.print("1,");
  } 
  else if (clik==1&&buttonState==HIGH){
    clik=0;
    // turn LED off:
    Serial.print("0,");
  }
  else {Serial.print("2,");}
  
  // RIGHT CLICK
   if (clik1==0&&button1State == LOW) {
   clik1=1;
    // turn LED on:
    Serial.println(1);
  } 
  else if (clik1==1&&button1State==HIGH){
    clik1=0;
    // turn LED off:
    Serial.println(0);
  }
  else {Serial.println(2);}
   //}
delay(0);
  
}
