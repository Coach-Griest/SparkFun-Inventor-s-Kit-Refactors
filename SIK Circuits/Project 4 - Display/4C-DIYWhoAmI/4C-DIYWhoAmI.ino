/*
  SparkFun Inventor’s Kit
  Circuit 4C - Heads Up Game

  This is a DIY version of the popular Heads Up party game. To play, one person resets the RedBoard and holds the LCD
  facing away from them so that they cannot see it (usually on their forehead). The display will show a short countdown
  then display random words. The other player(s) who can see the screen must yell out clues until time runs out or the player
  guesses what word is on the screen. If they guess correctly, they can press the button on the breadboard and another word
  will be displayed.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community
  and modified by Mitchell Griest in the summer of 2020.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>

// Follows the wiring diagram on page 84 of the SIK Guide
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// ----------------------- VARIABLE SETUP -----------------------

const int BUTTON_PIN = 2;
const int BUZZER_PIN = 6;

const int LCD_WIDTH = 16;
const int LCD_HEIGHT = 2;

const long TIME_LIMIT = 15 * 1000; // 15 seconds

long startTime = 0;
int timeLeftToGuessCurrentWord = 0;
int roundNumber;

const int NUM_OPTIONS = 25;

const char* category = "Animals";
const char* ANIMALS[NUM_OPTIONS] = {"moose", "beaver", "bear", "goose", "dog", "cat", "squirrel", "bird", "elephant", "horse",
                                    "bull", "giraffe", "seal", "bat", "skunk", "turtle", "whale", "rhino", "lion", "monkey",
                                    "frog", "alligator", "kangaroo", "hippo", "rabbit"
                                   };

int randomSequence[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

const int E4 = 130;
const int G3 = 73;
const int E3 = 65;
const int C3 = 98;
const int E6 = 1318;
const int G6 = 1567;
const int E7 = 2637;
const int C7 = 2093;
const int D7 = 2349;
const int G7 = 3135;

// ----------------------- CORE EXECUTION -----------------------

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  generateRandomOrder();
  showStartSequence();
}

void loop() {
  for (int i = 0; i < NUM_OPTIONS; i++) {
    lcd.clear();
    roundNumber = i + 1;

    showRoundNumber();
    showNextWordInRandomSequence();

    startTime = millis();

    while (!buttonIsPressed()) {
      int roundedTimeRemaining = getRoundedTimeRemaining();
      showRoundedTimeRemaining(roundedTimeRemaining);
      debounce();

      if (timeIsUp()) gameOver();
      if (buttonIsPressed()) playShortTone();
    }

    shortPauseBetweenRounds();
  }
  winner();
}

// ----------------------- HELPER FUNCTIONS -----------------------

void generateRandomOrder() {
  randomSeed(analogRead(0));
  for (int i = 0; i < NUM_OPTIONS; i++) {
    int currentNumber = random(0, NUM_OPTIONS);
    while (isIn(currentNumber, randomSequence, NUM_OPTIONS)) currentNumber = random(0, NUM_OPTIONS);
    randomSequence[i] = currentNumber;
  }
}

void showStartSequence() {
  showCategory();
  showGetReadyMessage();
  showCountDown(3);
}

void showCategory() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Category: ");
  lcd.setCursor(3, 1);
  lcd.print(category);
  delay(2000);
}

void showGetReadyMessage() {
  lcd.clear();
  lcd.print("Get ready!");
  delay(1000);
}

void showCountDown(int from) {
  for (int i = from; i > 0; i--) {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print(i);
    delay(1000);
  }
}

void showRoundNumber() {
  lcd.print(roundNumber);
  lcd.print(": ");
}

void showNextWordInRandomSequence() {
  lcd.print(ANIMALS[roundNumber - 1]);
}

int getRoundedTimeRemaining() {
  long ellpasedTime = millis() - startTime;
  return round((TIME_LIMIT - ellpasedTime ) / 1000);
}

void showRoundedTimeRemaining(int roundedTimeRemaining) {
  lcd.setCursor(14, 1);
  lcd.print("  "); // Clear the previous number
  lcd.setCursor(14, 1);
  lcd.print(roundedTimeRemaining);
}

void debounce() {
  delay(15);
}

boolean timeIsUp() {
  long ellapsedTime = millis() - startTime;
  return ellapsedTime > TIME_LIMIT;
}

void gameOver() {
  showGameOverMessage();
  showScore();
  playLosingFogHorn();
  stayHereForever();
}

void showGameOverMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over");
}

void showScore() {
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(roundNumber);
}

void playLosingFogHorn() {
  tone(BUZZER_PIN, E4, 250);
  delay(275);
  tone(BUZZER_PIN, G3, 250);
  delay(275);
  tone(BUZZER_PIN, E3, 150);
  delay(175);
  tone(BUZZER_PIN, C3, 500);
  delay(500);
}

void playShortTone() {
  tone(BUZZER_PIN, E6, 100);
}

void shortPauseBetweenRounds() {
  delay(500);
}

void winner() {
  showYouWinMessage();
  play1UpNoise();
  stayHereForever();
}

void showYouWinMessage() {
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("YOU");
  lcd.setCursor(7, 1);
  lcd.print("WIN!");
}

void play1UpNoise() {
  tone(BUZZER_PIN, E6, 150);
  delay(175);
  tone(BUZZER_PIN, G6, 150);
  delay(175);
  tone(BUZZER_PIN, E7, 150);
  delay(175);
  tone(BUZZER_PIN, C7, 150);
  delay(175);
  tone(BUZZER_PIN, D7, 150);
  delay(175);
  tone(BUZZER_PIN, G7, 500);
  delay(500);
}

void stayHereForever() {
  while (true) {}
}
