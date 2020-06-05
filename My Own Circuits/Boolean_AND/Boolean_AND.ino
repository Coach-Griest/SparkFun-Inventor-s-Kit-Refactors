/*
   Boolean AND circuit using two buttons and an LED
   by Mitchell Griest, Summer 2020

   TinkerCad Circuit link: https://www.tinkercad.com/things/68YpoLUPcnb
*/

const int LED_PIN  = 13;

const int BUTTON_A_PIN = 8;
const int BUTTON_B_PIN = 9;

// -------------- Main Execution --------------

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
}

void loop() {
  if (buttonAIsPressed() && buttonBIsPressed()) turnOnLed();
  else turnOffLed();

  delay(25); // Debounce buttons
}

// -------------- Helper Functions --------------

boolean buttonAIsPressed() {
  return buttonIsPressed(BUTTON_A_PIN);
}

boolean buttonBIsPressed() {
  return buttonIsPressed(BUTTON_B_PIN);
}

boolean buttonIsPressed(int buttonPin) {
  return digitalRead(buttonPin) == LOW;
}

void turnOnLed() {
  digitalWrite(LED_PIN, HIGH);
}

void turnOffLed() {
  digitalWrite(LED_PIN, LOW);
}
