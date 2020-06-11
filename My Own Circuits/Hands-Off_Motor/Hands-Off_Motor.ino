/*
   Ultrasonic Range Finder-Controlled Servo Motor
   by Mitchell Griest, Summer 2020

   TinkerCad Circuit link: https://www.tinkercad.com/things/gW6ZYSPnUl7
*/
#include <Servo.h> 

const int TRIGGER_PIN = 13;
const int ECHO_PIN = 12;
const int SERVO_PIN = 2;

Servo servo;
float servoPosition;

void setup(){
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN);

  Serial.begin(9600);
}

void loop(){
  float distanceToNearestObject = getDistanceToNearestObject();
  constrain(distanceToNearestObject, 0, 30);
  
  float newServoPosition = map(distanceToNearestObject, 0, 30, 20, 160);
  float changeInPosition = abs(servoPosition - newServoPosition);
  if(changeInPosition < 50){
    servo.write(newServoPosition);
    servoPosition = newServoPosition;
  }

  Serial.print("Distance: ");
  Serial.print(distanceToNearestObject);
  Serial.print("\tPosition: ");
  Serial.println(newServoPosition);
  
  delay(100);
}

float getDistanceToNearestObject() {
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  float echoTime = pulseIn(ECHO_PIN, HIGH);

  float calculatedDistance = echoTime / 148.0;

  return calculatedDistance;
}
