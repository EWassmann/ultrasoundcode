#include <NewPing.h>

#include "ArduinoSort.h"
int ultrasound (int trig, int echo){
  long Duration;
  int distance[5];
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  for (int i =0; i<5; i++){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  Duration = pulseIn(echo, HIGH);
  distance[i] = Duration * 0.034 / 2;
  }
  sortArray(distance,5);
  return distance[3];
}

int d;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

}

void loop() {
  delay(60);
d = ultrasound(3,2);

Serial.println(d);
}
