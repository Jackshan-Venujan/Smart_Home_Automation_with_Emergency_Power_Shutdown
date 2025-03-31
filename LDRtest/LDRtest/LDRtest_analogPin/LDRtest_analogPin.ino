int ldr = A0;  // LDR sensor connected to analog pin A0
int led = 13;  // LED connected to digital pin 13

void setup() {
  Serial.begin(9600);  // Start Serial Monitor
  pinMode(led, OUTPUT);  // Set LED pin as output
}

void loop() {
  int lightLevel = analogRead(ldr);  // Read LDR value (0-1023)
  Serial.println(lightLevel);  // Print LDR value to Serial Monitor

  if (lightLevel < 500) { // If dark, turn LED ON
    digitalWrite(led, HIGH);
  } else {  // If bright, turn LED OFF
    digitalWrite(led, LOW);
  }

  delay(500); // Wait 500ms before next reading
}

