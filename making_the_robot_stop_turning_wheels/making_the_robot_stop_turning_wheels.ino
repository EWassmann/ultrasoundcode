#include <Servo.h>
Servo servo1;
int servoPin1 = 9;
Servo servo2;
int servoPin2 = 11;
Servo servo3;
int servoPin3 = 10;


void setup(){
servo1.attach(servoPin1);

servo2.attach(servoPin2);

servo3.attach(servoPin3);
servo3.write(80);
//Serial.begin(9600);
}
void loop(){
  servo1.writeMicroseconds(1500);
  delay(10);
  servo2.writeMicroseconds(1500);
  delay(1000);
  servo3.write(80);
}
