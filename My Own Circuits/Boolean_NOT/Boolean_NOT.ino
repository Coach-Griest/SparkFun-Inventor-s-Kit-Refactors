const int ledPin = 13;
const int buttonPin = 8;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop(){
  if(buttonIsPressed()){
    turnOffLed();
  } else {
    turnOnLed();
  }
}

boolean buttonIsPressed(){
  return digitalRead(buttonPin) == LOW;
}

void turnOffLed(){
  digitalWrite(ledPin, LOW);
}

void turnOnLed(){
  digitalWrite(ledPin, HIGH);
}
