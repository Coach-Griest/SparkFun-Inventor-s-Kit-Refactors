/*
  SparkFun Inventor’s Kit
  Circuit 5B - Remote Control Robot

  Control a two wheeled robot by sending botDirection commands through the serial monitor.
  This sketch was adapted from one of the activities in the SparkFun Guide to Arduino.
  Check out the rest of the book at
  https://www.sparkfun.com/products/14326

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community
  and modified by Mitchell Griest in the summer of 2020.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

// ----------------------- VARIABLE SETUP -----------------------

// Right Motor Pins
const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;

// Left Motor Pins
const int PWMB = 10;
const int BIN2 = 9;
const int BIN1 = 8;

const int ON_OFF_SWITCH_PIN = 7;
const int TIME_TO_DRIVE_ONE_INCH = 20;
const int TIME_TO_TURN_ONE_DEGREE  = 8;

const int LINEAR_DRIVE_INTENSITY = 200;
const int TURNING_DRIVE_INTENSITY = 255;

String botDirection;
String distance;

// ----------------------- CORE EXECUTION -----------------------

void setup() {
  Serial.begin(9600);
  setupOnOffSwitch();
  setupMotorPins();
  promptUserForInput();
}

void loop() {
  if (switchIsOn()) {
    if (userHasSentCommand())  {
      botDirection = Serial.readStringUntil(' ');
      botDirection.toLowerCase();
      distance = Serial.readStringUntil(' ');

      repeatCommandBackToUser();
      moveBot();
    }
  } else {
    turnOffBothMotors();
  }
}

// ----------------------- MOTOR CONTROL -----------------------

void rightMotor(int motorSpeed) {
  if (shouldDriveForward(motorSpeed)) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else if (shouldDriveBackward(motorSpeed)) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  analogWrite(PWMA, abs(motorSpeed));
}


void leftMotor(int motorSpeed) {
  if (shouldDriveForward(motorSpeed)) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else if (shouldDriveBackward(motorSpeed)) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  analogWrite(PWMB, abs(motorSpeed));
}

// ----------------------- HELPER FUNCTIONS -----------------------

void setupOnOffSwitch() {
  pinMode(ON_OFF_SWITCH_PIN, INPUT_PULLUP);
}

void  setupMotorPins() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void promptUserForInput() {
  Serial.println("Enter a botDirection followed by a distance.");
  Serial.println("f = forward, b = backward, r = turn right, l = turn left");
  Serial.println("Example command: f 50");
}

boolean switchIsOn() {
  return digitalRead(7) == LOW;
}

boolean userHasSentCommand() {
  return Serial.available() > 0;
}

void repeatCommandBackToUser() {
  Serial.print(botDirection);
  Serial.print(" ");
  Serial.println(distance.toInt());
}

boolean shouldDriveForward(int motorSpeed) {
  return motorSpeed > 0;
}

boolean shouldDriveBackward(int motorSpeed) {
  return motorSpeed < 0;
}

void moveBot() {
  if (botDirection == "f") moveForward();
  else if (botDirection == "b") moveBackward();
  else if (botDirection == "r") moveRight();
  else if (botDirection == "l") moveLeft();
  else Serial.println("Unrecognized direction: " + botDirection);
}

void moveForward() {
  rightMotor(LINEAR_DRIVE_INTENSITY);
  leftMotor(LINEAR_DRIVE_INTENSITY);
  delay(TIME_TO_DRIVE_ONE_INCH * distance.toInt());
  turnOffBothMotors();
}

void moveBackward() {
  rightMotor(-LINEAR_DRIVE_INTENSITY);
  leftMotor(-LINEAR_DRIVE_INTENSITY);
  delay(TIME_TO_DRIVE_ONE_INCH * distance.toInt());
  turnOffBothMotors();
}

void moveRight() {
  rightMotor(-LINEAR_DRIVE_INTENSITY);
  leftMotor(TURNING_DRIVE_INTENSITY);
  delay(TIME_TO_TURN_ONE_DEGREE * distance.toInt());
  turnOffBothMotors();
}

void moveLeft() {
  rightMotor(TURNING_DRIVE_INTENSITY);
  leftMotor(-LINEAR_DRIVE_INTENSITY);
  delay(TIME_TO_TURN_ONE_DEGREE * distance.toInt());
  turnOffBothMotors();
}

void turnOffBothMotors() {
  rightMotor(0);
  leftMotor(0);
}
