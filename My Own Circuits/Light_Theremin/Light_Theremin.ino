/*
   Basic version of the Light-Controlled Theremin
   using Piezo Speaker, Potentiometer, and Photoresistor
   by Mitchell Griest, Summer 2020

   TinkerCad Circuit link: https://www.tinkercad.com/things/26D7noXK8uq
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
  delay(duration * 1.1);
}

// -------------- Helper Functions --------------

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
  } else if (knobValue < 1000) {
    play('b', duration);
  } else {
    play('C', duration);
  }
}

void play(char note, int duration){
  int frequency = 0;
  
  if(note == 'c') frequency = 262;
  else if(note == 'd') frequency = 294;
  else if(note == 'e') frequency = 330;
  else if(note == 'f') frequency = 349;
  else if(note == 'g') frequency = 392;
  else if(note == 'a') frequency = 440;
  else if(note == 'b') frequency = 494;
  else if(note == 'C') frequency = 523;
    
  tone(BUZZER_PIN, frequency, duration);
}
