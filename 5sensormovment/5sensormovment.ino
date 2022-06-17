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
//ultrasound setup
#define echoPinF 2 
#define trigPinF 3 
#define echoPinR 5
#define trigPinR 4
#define trigPinL 6
#define echoPinL 7
#define echoPinFR 18
#define trigPinFR 19
#define echoPinFL 20
#define trigPinFL 21
long durationF; // variable for the duration of sound wave travel
long durationR;
long durationL;
long durationFR;
long durationFL;

int distanceF; // variable for the distance measurement
int distanceR;
int distanceL;
int distanceFR;
int distanceFL;

void setup(){
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  pinMode(trigPinF, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinF, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinFR, OUTPUT);
  pinMode(echoPinFR, INPUT);
  pinMode(trigPinFL, OUTPUT);
  pinMode(echoPinFL, INPUT);
  Serial.begin(9600);
  servo3.write(80);
  delay(100);
}


void loop(){
  //front sensor
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);
  durationF = pulseIn(echoPinF, HIGH);
  distanceF = durationF * 0.034 / 2;
//left sensor
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = durationL * 0.034 / 2;
//Right sensor
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = durationR * 0.034 / 2;
//Front left sensor
  digitalWrite(trigPinFL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinFL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFL, LOW);
  durationFL = pulseIn(echoPinFL, HIGH);
  distanceFL = durationFL * 0.034 / 2;
  //front right sensor
  digitalWrite(trigPinFR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinFR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFR, LOW);
  durationFR = pulseIn(echoPinFR, HIGH);
  distanceFR = durationFR * 0.034 / 2;
Serial.println(distanceF);
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
    //no obstruction in front
  }else if (distanceF>100){
      //front left obstruction only
      if(distanceFL <100){
        servo1.writeMicroseconds(2000);
        servo2.writeMicroseconds(1000);
        servo3.write(90);
      }
      //front right obstruction only
      if (distanceFR<100){
       servo1.writeMicroseconds(1000);
        servo2.writeMicroseconds(2000);
        servo3.write(90);
      }
      //allgood conditions
      if ( distanceFR>100 && distanceFL >100){
      servo1.writeMicroseconds(1500);
      servo2.writeMicroseconds(1500);
      servo3.write(94); 
  }
    
  }
  //delays to make less jerky may not be needed
delay(250);
  //stop conditions
}else{
  //reverse gear set 3 to 80 for stopped bot
  servo3.write(60);
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  //may need to be made shorter or longer
  delay(300);
}
}//for void loop dont deleat
