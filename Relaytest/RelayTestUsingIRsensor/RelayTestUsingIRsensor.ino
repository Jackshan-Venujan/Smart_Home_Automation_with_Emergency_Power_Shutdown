const int relayPin = 7;      // Pin connected to the relay
const int irSensorPin = 2;   // Pin connected to the IR sensor

void setup() {
  pinMode(relayPin, OUTPUT);  // Set relay pin as output
  pinMode(irSensorPin, INPUT); // Set IR sensor pin as input
  Serial.begin(9600);         // Start serial communication at 9600 baud rate
}

void loop() {
  int irValue = digitalRead(irSensorPin); // Read the IR sensor value
  int relayStatus = digitalRead(relayPin); // Read the relay pin status

  // Print the current values of the relay and IR sensor
  Serial.print("IR Sensor Value: ");
  Serial.print(irValue);
  Serial.print(" | Relay Status: ");
  Serial.println(relayStatus == HIGH ? "ON" : "OFF"); // Print ON/OFF based on relay status

  // Control the relay based on the IR sensor value
  if (irValue == 0) {  // If IR sensor input is 1 (sensor detected something)
    digitalWrite(relayPin, LOW);  // Turn the relay OFF (system off)
    Serial.println("System OFF");
  } else {  // If IR sensor input is 0 (no detection)
    digitalWrite(relayPin, HIGH);  // Turn the relay ON (system on)
    Serial.println("System ON");
  }

  delay(1000);  // Wait for 1 second before checking the sensor again
}

