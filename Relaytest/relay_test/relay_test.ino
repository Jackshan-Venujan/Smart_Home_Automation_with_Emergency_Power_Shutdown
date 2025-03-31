const int relayPin = 7;      // Pin connected to the relay
const int irSensorPin = A1;   // Pin connected to the IR sensor
const int buzzerPin = 6;     // Pin connected to the passive buzzer

void setup() {
  pinMode(relayPin, OUTPUT);  // Set relay as output
  pinMode(irSensorPin, INPUT); // Set IR sensor as input
  pinMode(buzzerPin, OUTPUT);  // Set buzzer as output
  Serial.begin(9600);         // Start serial communication
}

void loop() {
  int irValue = digitalRead(irSensorPin); // Read IR sensor value
  int relayStatus = digitalRead(relayPin); // Read relay status

  // Print the current values of the relay and IR sensor
  Serial.print("IR Sensor Value: ");
  Serial.print(irValue);
  Serial.print(" | Relay Status: ");
  Serial.println(relayStatus == HIGH ? "ON" : "OFF");

  // If IR sensor detects something
  if (irValue == 0) {
    digitalWrite(relayPin, LOW);   // Turn relay OFF (interrupt power)
    tone(buzzerPin, 2000);         // Generate a 1000Hz beep sound
    delay(100);

    Serial.println("System OFF | Buzzer ON (Intruder Detected)");
  } else {  
    digitalWrite(relayPin, HIGH);  // Turn relay ON (restore power)
    noTone(buzzerPin);             // Stop the buzzer
    Serial.println("System ON | Buzzer OFF (No Detection)");
  }

  delay(1000);  // Wait 1 second before checking again
}







