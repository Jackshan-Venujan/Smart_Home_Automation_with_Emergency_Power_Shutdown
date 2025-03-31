const int relayPin = 7;      // Pin connected to the relay
const int gasSensorPin = A1; // Pin connected to the gas sensor (analog input)
const int buzzerPin = 6;     // Pin connected to the passive buzzer

const int thresholdPPM = 600;   // Gas detection threshold in PPM (adjust as needed)

const float VCC = 5.0;   // Arduino operating voltage
const float R0 = 10.0;   // Sensor resistance in clean air (calibrate this value)

bool gasDetected = false; // Flag to keep track of whether gas is detected

void setup() {
  pinMode(relayPin, OUTPUT);  // Set relay as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer as output
  digitalWrite(relayPin, HIGH); // Set relay ON initially
  Serial.begin(9600);         // Start serial communication
}

void loop() {
  if (!gasDetected) {  // Only check the sensor if gas is not yet detected
    int sensorValue = analogRead(gasSensorPin); // Read gas sensor value
    float voltage = (sensorValue / 1023.0) * VCC; // Convert to voltage

    // Calculate RS (sensor resistance in gas presence)
    float RS = ((VCC * 10.0) / voltage) - 10.0;

    // Convert to PPM using logarithmic formula (values A & B from datasheet)
    float CO_PPM = 10 * pow((RS / R0), -1.5);   // Example formula for CO
    float Smoke_PPM = 10 * pow((RS / R0), -1.2); // Example formula for Smoke
    float Gas_PPM = 10 * pow((RS / R0), -1.8);   // Example formula for Gas

    int relayStatus = digitalRead(relayPin); // Read relay status

    // Print Gas PPM values in Serial Monitor
    Serial.print("CO PPM: "); Serial.print(CO_PPM);
    Serial.print(" | Smoke PPM: "); Serial.print(Smoke_PPM);
    Serial.print(" | Gas PPM: "); Serial.print(Gas_PPM);
    Serial.print(" | Relay Status: "); Serial.println(relayStatus == HIGH ? "ON" : "OFF");

    // If any gas value exceeds the threshold, set gasDetected to true
    if (CO_PPM > thresholdPPM || Smoke_PPM > thresholdPPM || Gas_PPM > thresholdPPM) {  
      gasDetected = true;  // Set persistent alarm state
      Serial.println("⚠️ Gas Detected! Alarm Activated ⚠️");
    }
  }

  // **Persistent Alarm State (after gas detection)**:
  if (gasDetected) {
    digitalWrite(relayPin, LOW);  // Keep relay OFF
    //tone(buzzerPin, 2000);        // Buzzer keeps beeping continuously
     for (int i = 0; i < 3; i++) {
      tone(buzzerPin, 2000);
      delay(200);
      noTone(buzzerPin);
    delay(200);
  }
    Serial.println("🚨 System OFF | Buzzer ON (Manual Reset Required) 🚨");
  }

  delay(1000);  // Wait 1 second before checking again
}



/*
const int relayPin = 7;      // Pin connected to the relay
const int gasSensorPin = A1; // Pin connected to the gas sensor (analog input)
const int buzzerPin = 6;     // Pin connected to the passive buzzer

const int thresholdPPM = 600;   // Gas detection threshold in PPM (adjust as needed)

const float VCC = 5.0;   // Arduino operating voltage
const float R0 = 10.0;   // Sensor resistance in clean air (calibrate this value)

bool gasDetected = false; // Persistent alarm state

void setup() {
  pinMode(relayPin, OUTPUT);  // Set relay as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer as output
  Serial.begin(9600);         // Start serial communication
}

void loop() {
  if (!gasDetected) {  // Only check sensor if alarm hasn't been triggered
    int sensorValue = analogRead(gasSensorPin); // Read gas sensor value
    float voltage = (sensorValue / 1023.0) * VCC; // Convert to voltage
    
    // Calculate RS (sensor resistance in gas presence)
    float RS = ((VCC * 10.0) / voltage) - 10.0;

    // Convert to PPM using logarithmic formula (values A & B from datasheet)
    float CO_PPM = 10 * pow((RS / R0), -1.5);   // Example formula for CO
    float Smoke_PPM = 10 * pow((RS / R0), -1.2); // Example formula for Smoke
    float Gas_PPM = 10 * pow((RS / R0), -1.8);   // Example formula for Gas

    int relayStatus = digitalRead(relayPin); // Read relay status

    // Print Gas PPM values in Serial Monitor
    Serial.print("CO PPM: "); Serial.print(CO_PPM);
    Serial.print(" | Smoke PPM: "); Serial.print(Smoke_PPM);
    Serial.print(" | Gas PPM: "); Serial.print(Gas_PPM);
    Serial.print(" | Relay Status: "); Serial.println(relayStatus == HIGH ? "ON" : "OFF");

    // If any gas value exceeds the threshold, trigger alarm state
    if (CO_PPM > thresholdPPM || Smoke_PPM > thresholdPPM || Gas_PPM > thresholdPPM) {  
      gasDetected = true;  // Set persistent alarm state
      Serial.println("⚠️ Gas Detected! Alarm Activated ⚠️");
    }
  }

  // **Persistent Alarm State:**
  if (gasDetected) {
    digitalWrite(relayPin, LOW);  // Keep relay OFF
    tone(buzzerPin, 2000);        // Buzzer keeps beeping continuously
    Serial.println("🚨 System OFF | Buzzer ON (Manual Reset Required) 🚨");
  }

  delay(1000);  // Wait 1 second before checking again
}

*/













/*
const int relayPin = 7;      // Pin connected to the relay
const int gasSensorPin = A1; // Pin connected to the gas sensor (analog input)
const int buzzerPin = 6;     // Pin connected to the passive buzzer

const int thresholdPPM = 600;   // Gas detection threshold in PPM (adjust as needed)

const float VCC = 5.0;   // Arduino operating voltage
const float R0 = 10.0;   // Sensor resistance in clean air (calibrate this value)

void setup() {
  pinMode(relayPin, OUTPUT);  // Set relay as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer as output
  Serial.begin(9600);         // Start serial communication
}

void loop() {
  int sensorValue = analogRead(gasSensorPin); // Read gas sensor value
  float voltage = (sensorValue / 1023.0) * VCC; // Convert to voltage
  
  // Calculate RS (sensor resistance in gas presence)
  float RS = ((VCC * 10.0) / voltage) - 10.0;

  // Convert to PPM using logarithmic formula (values A & B are from the datasheet)
  float CO_PPM = 10 * pow((RS / R0), -1.5);  // Example formula for CO
  float Smoke_PPM = 10 * pow((RS / R0), -1.2);  // Example formula for Smoke
  float Gas_PPM = 10 * pow((RS / R0), -1.8);  // Example formula for Gas

  int relayStatus = digitalRead(relayPin); // Read relay status

  // Print Gas PPM values in Serial Monitor
  Serial.print("CO PPM: "); Serial.print(CO_PPM);
  Serial.print(" | Smoke PPM: "); Serial.print(Smoke_PPM);
  Serial.print(" | Gas PPM: "); Serial.print(Gas_PPM);
  Serial.print(" | Relay Status: "); Serial.println(relayStatus == HIGH ? "ON" : "OFF");

  // If any gas value exceeds the threshold
  if (CO_PPM > thresholdPPM || Smoke_PPM > thresholdPPM || Gas_PPM > thresholdPPM) {  
    digitalWrite(relayPin, LOW);  // Turn relay OFF (interrupt power)
    tone(buzzerPin, 2000, 500);   // Generate a 2000Hz beep for 500ms
    Serial.println("System OFF | Buzzer ON (Gas Detected)");
  } else {  
    digitalWrite(relayPin, HIGH); // Turn relay ON (restore power)
    noTone(buzzerPin);            // Stop the buzzer
    Serial.println("System ON | Buzzer OFF (No Gas Detected)");
  }
 
  delay(1000);  // Wait 1 second before checking again
}
*/


