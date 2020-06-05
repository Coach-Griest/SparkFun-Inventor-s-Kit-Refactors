/*
 * Boolean NOT circuit using a button and an LED
 * by Mitchell Griest, Summer 2020
 * 
 * TinkerCad Circuit link: https://www.tinkercad.com/things/a5petd4HbrE-mighty-luulia-esboo/editel?tenant=circuits?sharecode=Mismn8_1YfFj8bcDSD2uctGl2eyOH_kL8kJZgohA7eM
 */

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
