/*
 * Boolean NOT circuit using a button and an LED
 * by Mitchell Griest, Summer 2020
 * 
 * TinkerCad Circuit link: https://www.tinkercad.com/things/a5petd4HbrE
 */

const int LED_PIN = 13;
const int BUTTON_PIN = 8;

// -------------- Main Execution --------------

void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop(){
  if(buttonIsPressed()) turnOffLed();
  else turnOnLed();
  delay(25); //Debounce the button
}

// -------------- Helper Functions --------------

boolean buttonIsPressed(){
  return digitalRead(BUTTON_PIN) == LOW;
}

void turnOffLed(){
  digitalWrite(LED_PIN, LOW);
}

void turnOnLed(){
  digitalWrite(LED_PIN, HIGH);
}
