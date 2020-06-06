const int RED_BUTTON = 2;
const int YELLOW_BUTTON = 3;
const int GREEN_BUTTON = 4;
const int BLUE_BUTTON = 5;

const int BUZZER_PIN = 9;

void setup(){
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop(){
  if(redButtonIsPressed()) play('c');
  else if(yellowButtonIsPressed() && greenButtonIsPressed()) play('b');
  else if(yellowButtonIsPressed()) play('d');
  else if(greenButtonIsPressed()) play('e');
  else if(blueButtonIsPressed()) play('a');
  else stopBuzzer();
}

// ------------ HELPER FUNCTIONS ------------

boolean buttonIsPressed(int buttonPin){
  return digitalRead(buttonPin) == LOW;
}

boolean redButtonIsPressed(){
  return buttonIsPressed(RED_BUTTON);
}

boolean yellowButtonIsPressed(){
  return buttonIsPressed(YELLOW_BUTTON);
}

boolean greenButtonIsPressed(){
  return buttonIsPressed(GREEN_BUTTON);
}

boolean blueButtonIsPressed(){
  return buttonIsPressed(BLUE_BUTTON);
}

void play(char note){
  if(note == 'c') tone(BUZZER_PIN, 262);
  else if(note == 'd') tone(BUZZER_PIN, 294);
  else if(note == 'e') tone(BUZZER_PIN, 330);
  else if(note == 'a') tone(BUZZER_PIN, 440);
  else if(note == 'b') tone(BUZZER_PIN, 494);
}

void stopBuzzer(){
  noTone(BUZZER_PIN);
}
