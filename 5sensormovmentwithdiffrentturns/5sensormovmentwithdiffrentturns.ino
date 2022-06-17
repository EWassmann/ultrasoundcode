#include <Arduino.h>
#include <Servo.h>
#include "NewPing.h"
//code to make the robot move around and avoid obsticals better
// servo setup
Servo servo1;
int servoPin1 = 9;
Servo servo2;
int servoPin2 = 11;
Servo servo3;
int servoPin3 = 10;
//ultrasound setup
#define Sonar_Num 5
//float distanceF;
//float distanceR;
//float dstnaceL;
//float distanceFR;
//float distanceFL;
NewPing sonar[Sonar_Num]= {
  NewPing(3, 2, 1200),
  NewPing(4, 5, 1200),
  NewPing(6, 7, 1200),
  NewPing(19, 18, 1200),
  NewPing(21, 20, 1200)
  };
  
  
//#define echoPinF 2 
//#define trigPinF 3 
//
//#define echoPinR 5
//#define trigPinR 4
//#define trigPinL 6
//#define echoPinL 7
//#define echoPinFR 18
//#define trigPinFR 19
//#define echoPinFL 20
//#define trigPinFL 21
//long durationF; // variable for the duration of sound wave travel
//long durationR;
//long durationL;
//long durationFR;
//long durationFL;
//
int distanceF; // variable for the distance measurement
int distanceR;
int distanceL;
int distanceFL;
int distanceFR;

void setup(){
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
//  pinMode(trigPinF, OUTPUT); // Sets the trigPin as an OUTPUT
//  pinMode(echoPinF, INPUT); // Sets the echoPin as an INPUT
//  pinMode(trigPinR, OUTPUT);
//  pinMode(echoPinR, INPUT);
//  pinMode(trigPinL, OUTPUT);
//  pinMode(echoPinL, INPUT);
//  pinMode(trigPinFR, OUTPUT);
//  pinMode(echoPinFR, INPUT);
//  pinMode(trigPinFL, OUTPUT);
//  pinMode(echoPinFL, INPUT);
  Serial.begin(9600);
  servo3.write(80);
  delay(100);
}


void loop(){
//  //front sensor
//  digitalWrite(trigPinF, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPinF, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPinF, LOW);
//  durationF = pulseIn(echoPinF, HIGH);
//  distanceF = durationF * 0.034 / 2;
////left sensor
//  digitalWrite(trigPinL, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPinL, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPinL, LOW);
//  durationL = pulseIn(echoPinL, HIGH);
//  distanceL = durationL * 0.034 / 2;
////Right sensor
//  digitalWrite(trigPinR, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPinR, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPinR, LOW);
//  durationR = pulseIn(echoPinR, HIGH);
//  distanceR = durationR * 0.034 / 2;
////Front left sensor
//  digitalWrite(trigPinFL, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPinFL, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPinFL, LOW);
//  durationFL = pulseIn(echoPinFL, HIGH);
//  distanceFL = durationFL * 0.034 / 2;
//  //front right sensor
//  digitalWrite(trigPinFR, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPinFR, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPinFR, LOW);
//  durationFR = pulseIn(echoPinFR, HIGH);
//  distanceFR = durationFR * 0.034 / 2;

//trying NewPing
distanceF = sonar[1].ping_cm();
delay(1000);
distanceR = sonar[2].ping_cm();
delay(1000);
distanceL = sonar[3].ping_cm();
delay(1000);
distanceFR = sonar[4].ping_cm();
delay(1000);
distanceFL = sonar[5].ping_median();

Serial.println(distanceL);

//decision making and steering
if (distanceF>15 && distanceFR>15 && distanceFL>15){

  
  //an obstruction in front 
  if (distanceF<100){
    //only in front
    if (distanceFR>100 && distanceFL>100){
      if (distanceL>distanceR  ){
        servo1.writeMicroseconds(1000);
        servo2.writeMicroseconds(2000);
        servo3.write(90);
      }
        if(distanceL<distanceR){
        servo1.writeMicroseconds(2000);
        servo2.writeMicroseconds(1000);
        servo3.write(90);
        }
    }
    //front and right
    if (distanceFR<100 && distanceFL>100){
   
        servo1.writeMicroseconds(1000);
        servo2.writeMicroseconds(2000);
        servo3.write(90);
     
    }
    //front and left
       if (distanceFR>100 && distanceFL<100){
        servo1.writeMicroseconds(2000);
        servo2.writeMicroseconds(1000);
        servo3.write(90);

        }
    delay(10);
    //no obstruction in front
  }else if (distanceF>100){
      //front left obstruction only
      if(distanceFL <150){
        if(distanceFL<100){
        servo1.writeMicroseconds(2000);
        servo2.writeMicroseconds(1000);
        servo3.write(90);
        }else{
          servo1.writeMicroseconds(1650);
          servo2.writeMicroseconds(1350);
          servo3.write(94);
        }
        delay(10);
      }
      //front right obstruction only
      if (distanceFR<150){
        if (distanceFR<100){
       servo1.writeMicroseconds(1000);
        servo2.writeMicroseconds(2000);
        servo3.write(90);
        }else{
       servo1.writeMicroseconds(1350);
      servo2.writeMicroseconds(1650);
      servo3.write(94);
        }
        delay(10);
      }
      //allgood conditions
      if ( distanceFR>100 && distanceFL >100){
      servo1.writeMicroseconds(1500);
      servo2.writeMicroseconds(1500);
      servo3.write(94); 
      delay(300);
  }
  } 
  
  //delays to make less jerky may not be needed

  //stop conditions
}else{
  //reverse gear set 3 to 80 for stopped bot
  servo3.write(60);
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  //may need to be made shorter or longer
  delay(750);
  servo3.write(80);
  delay(50);
}
}//for void loop dont deleat
