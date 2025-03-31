const int buzzerPin = 6;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  tone(buzzerPin, 2000); // 1000Hz frequency (adjust if needed)
  delay(100);
  noTone(buzzerPin);
  delay(100);
}

