/*
   Light-Controlled Theremin using
   Piezo Speaker, Potentiometer, and Photoresistor
   by Mitchell Griest, Summer 2020

   TinkerCad Circuit link:
*/

const int BUZZER_PIN = 10;
const int POTENTIOMETER_PIN = A0;
const int PHOTORESISTOR_PIN = A1;

// -------------- Main Execution --------------

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int knobValue = analogRead(POTENTIOMETER_PIN);
  int lightValue = analogRead(PHOTORESISTOR_PIN);
  int duration = lightValue;
  playNoteFromKnob(knobValue, duration);
  delay(duration* 1.1);
}

void playNoteFromKnob(int knobValue, int duration) {
  if (knobValue < 150) {
    play('c', duration);
  } else if (knobValue < 300) {
    play('d', duration);
  } else if (knobValue < 450) {
    play('e', duration);
  } else if (knobValue < 600) {
    play('f', duration);
  } else if (knobValue < 750) {
    play('g', duration);
  } else if (knobValue < 900) {
    play('a', duration);
  } else if (knobValue < 900) {
    play('b', duration);
  } else {
    play('C', duration);
  }
}

void play(char note, int duration) {
  if (note == 'c') tone(BUZZER_PIN, 262, duration);
  else if (note == 'd') tone(BUZZER_PIN, 294, duration);
  else if (note == 'e') tone(BUZZER_PIN, 330, duration);
  else if (note == 'f') tone(BUZZER_PIN, 349, duration);
  else if (note == 'g') tone(BUZZER_PIN, 392, duration);
  else if (note == 'a') tone(BUZZER_PIN, 440, duration);
  else if (note == 'b') tone(BUZZER_PIN, 494, duration);
  else if (note == 'C') tone(BUZZER_PIN, 523, duration);
}
