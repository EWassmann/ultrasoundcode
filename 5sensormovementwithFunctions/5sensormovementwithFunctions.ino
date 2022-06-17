#include <Arduino.h>
#include <Servo.h>
//code to make the robot move around and avoid obsticals better
// servo setup
Servo servo1;
int servoPin1 = 9;
Servo servo2;
int servoPin2 = 11;
Servo servo3;
int servoPin3 = 10;


//function to ping the sensor
int ultrasound (int trig, int echo){
  long Duration;
  int distance;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
   digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  Duration = pulseIn(echo, HIGH);
  distance = Duration * 0.034 / 2;
  return distance;
}
//functions to make the robot turn right
void SharpRight(){
  servo1.writeMicroseconds(2200);
  servo2.writeMicroseconds(800);
}
void ShallowRight(){
  servo1.writeMicroseconds(1800);
  servo2.writeMicroseconds(1200);
}
//functions to make the robot turn left
void SharpLeft(){
  servo1.writeMicroseconds(800);
  servo2.writeMicroseconds(2200);
}
void ShallowLeft(){
  servo1.writeMicroseconds(1200);
  servo2.writeMicroseconds(1800);
}
//functions to make the robot go straight
void Straight(){
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
}
//functions to make the robot go, stop
void Stop(){
  servo3.write(80);
}
void GoFast(){
  servo3.write(1550);
}
void GoSlow(){
  servo3.write(1470);
}
void Reverse (){
  servo3.write(60);
}
int distanceF; // variable for the distance measurement
int distanceR;
int distanceL;
int distanceFR;
int distanceFL;

void setup(){
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  Serial.begin(9600);
  servo3.write(80);
  delay(100);
}



void loop(){
  //front sensor

distanceF = ultrasound(3,2);
//left sensor
distanceL = ultrasound(6, 7);
//Right sensor
 distanceR = ultrasound(4,5);
//Front left sensor
distanceFL = ultrasound(21,20);
//front right sensor
distanceFR = ultrasound(19, 18);

//decision making and steering
if (distanceF>15 && distanceFR>15 && distanceFL>15){

  
  //an obstruction in front 
  if (distanceF<100){
    //only in front
    if (distanceFR>100 && distanceFL>100){
      if (distanceL>distanceR  ){
        SharpLeft();
        GoSlow();
      }
        if(distanceL<distanceR){
       SharpRight();
        GoSlow();
        }
    }
    //front and right
    if (distanceFR<100 && distanceFL>100){
        SharpLeft();
        GoSlow();
    }
    //front and left
       if (distanceFR>100 && distanceFL<100){
      SharpRight();
        GoSlow();
    }
    //no obstruction in front
  }else if (distanceF>100){
      //front left obstruction only
      if(distanceFL <100){
        ShallowRight();
        GoSlow();
      }
      //front right obstruction only
      if (distanceFR<100){
       ShallowLeft();
        GoSlow();
      }
      //allgood conditions
      if ( distanceFR>100 && distanceFL >100){
      Straight();
      GoFast(); 
  }
    
  }
  //delays to make less jerky may not be needed
delay(200);
  //stop conditions
}else{
  //reverse gear set 3 to 80 for stopped bot
  Reverse();
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  //may need to be made shorter or longer
  delay(600);
  Stop();
}
}//for void loop dont deleat
