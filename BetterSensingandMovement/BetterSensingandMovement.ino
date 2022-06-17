#include <NewPing.h>

#include <Arduino.h>
#include <Servo.h>
#include <NewPing.h>
//code to make the robot move around and avoid obsticals better
// servo setup
Servo servo1;
int servoPin1 = 9;
Servo servo2;
int servoPin2 = 11;
Servo servo3;
int servoPin3 = 10;

#define Sonar_num 5
//function to ping the sensor
NewPing sonar[Sonar_num] = {
  NewPing(3, 2, 2000),
  NewPing(4, 5, 2000),
  NewPing(6, 7, 2000),
  NewPing(19, 18, 2000),
  NewPing(21, 20, 2000)
};
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
  servo3.write(1500);
}
void GoSlow(){
  servo3.write(1450);
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
  Serial.begin(115200);
  servo3.write(80);
  delay(1000);
}



void loop(){
  //front sensor
distanceF = sonar[0].ping_median(5) *.0343 /2 ;
delay(30);
//left sensor
distanceR = sonar[1].ping_median(5)*.0343 /2;
delay(30);
//Right sensor
 distanceL = sonar[2].ping_median(5)*.0343 /2;
 delay(50);
//Front right sensor
distanceFR = sonar[3].ping_median(5)*.0343 /2;
delay(50);
//front left sensor
distanceFL =sonar[4].ping_median(5)*.0343 /2;
delay(50);
//Serial.print("F:");
//Serial.println(distanceF);
//Serial.print("R:");
//Serial.println(distanceR);
//Serial.print("L:");
//Serial.println(distanceL);
//Serial.print("FR:");
//Serial.println(distanceFR);
//Serial.print("FL:");
//Serial.println(distanceFL);

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
//delay(200);
  //stop conditions
}else{
  //reverse gear set 3 to 80 for stopped bot
  
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  Reverse();
  //may need to be made shorter or longer
  delay(600);
  Stop();
}
}//for void loop dont deleat
