const int buzzerPin = 6;  // Pin connected to the buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
}

void sosBeep() {
  // S: Three short beeps
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }

  // O: Three long beeps
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000);
    delay(600);
    noTone(buzzerPin);
    delay(200);
  }

  // S: Three short beeps
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }

  delay(1000); // Pause before repeating
}

void loop() {
  sosBeep();
}















