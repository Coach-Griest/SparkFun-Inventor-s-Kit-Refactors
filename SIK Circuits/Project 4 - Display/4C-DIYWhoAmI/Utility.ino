boolean isIn(int targetNumber, int sequence[], int len) {
  for (int i = 0; i < len; i++) {
    if (sequence[i] == targetNumber) return true;
  }
  return false;
}

boolean buttonIsPressed() {
  return digitalRead(BUTTON_PIN) == LOW;
}
