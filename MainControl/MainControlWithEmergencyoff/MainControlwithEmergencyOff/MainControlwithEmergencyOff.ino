#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define LCD (I2C address: 0x27, 16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define DHT sensor
#define DHTPIN 8      // DHT11 connected to digital pin 8
#define DHTTYPE DHT11 // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// Define motor driver pins
#define ENA 9   // PWM pin for speed control
#define IN1 10  // Motor direction
#define IN2 11  // Motor direction

// Define LDR and LED
#define LDR_PIN A0   // LDR sensor analog pin
#define LED_PIN 13   // LED output pin

const int relayPin = 7;      // Pin connected to the relay
const int gasSensorPin = A1; // Pin connected to the gas sensor (analog input)
const int buzzerPin = 6;     // Pin connected to the passive buzzer

const int thresholdPPM = 400;   // Gas detection threshold in PPM (adjust as needed)

const float VCC = 5.0;   // Arduino operating voltage
const float R0 = 10.0;   // Sensor resistance in clean air (calibrate this value)

bool gasDetected = false; // Flag to keep track of whether gas is detected



void setup() {
  Serial.begin(9600); // Start Serial Monitor
  Serial.println("Temperature & LDR-Based Fan and Light Controller Initialized");

  //pinMode(5, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Fan & Light Ctrl");

  // Initialize DHT sensor
  dht.begin();

  // Set motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set LED as output
  pinMode(LED_PIN, OUTPUT);

  // Ensure fan is off initially
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  // Ensure LED is OFF initially
  digitalWrite(LED_PIN, LOW);

  //Emergency Power Off
  pinMode(relayPin, OUTPUT);  // Set relay as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer as output
  digitalWrite(relayPin, HIGH); // Set relay ON initially
  Serial.begin(9600);         // Start serial communication
}

void loop() {
  //digitalWrite(13, HIGH); 

  // Read temperature and humidity from DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read LDR sensor value
  int ldrValue = analogRead(LDR_PIN);

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


    // Check if the temperature reading is valid
      if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error: Failed to read from DHT11 sensor!");
        lcd.setCursor(0, 0);
        lcd.print("Temp Error!      ");
      } else {
        // Print temperature, humidity, and LDR value on LCD
        lcd.setCursor(0, 0);
        lcd.print("T: ");
        lcd.print(temperature);
        lcd.print("C H: ");
        lcd.print(humidity);
        lcd.print("% ");

        lcd.setCursor(0, 1);
        lcd.print("LDR: ");
        lcd.print(ldrValue);
        lcd.print("    "); // Clear previous characters

        // Print values on Serial Monitor
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" C, Humidity: ");
        Serial.print(humidity);
        Serial.print("%, LDR Value: ");
        Serial.println(ldrValue);

        // Control fan speed based on temperature
        int fanSpeed = 0;

        if (temperature < 25) {
          fanSpeed = 0; // Fan OFF
        } else if (temperature >= 25 && temperature < 30) {
          fanSpeed = 100; // Low speed
        } else if (temperature >= 30 && temperature < 35) {
          fanSpeed = 150; // Medium speed
        } else {
          fanSpeed = 255; // High speed
        }

        // Print fan speed on Serial Monitor
        Serial.print("Fan Speed: ");
        Serial.println(fanSpeed);

        // Control motor driver (fan)
        if (fanSpeed > 0) {
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
        } else {
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
        }

        analogWrite(ENA, fanSpeed); // Set speed

        // Print fan status on LCD
        lcd.setCursor(9, 1);
        lcd.print("Fan:");
        lcd.print(fanSpeed);
        lcd.print("  "); // Clear previous digits
      }

      // Control LED based on LDR value
      if (ldrValue > 800) {  
        digitalWrite(LED_PIN, HIGH); // Turn LED ON
        Serial.println("LED: ON");
      } else if (ldrValue < 600){
        digitalWrite(LED_PIN, LOW); // Turn LED OFF
        Serial.println("LED: OFF");
      }

      delay(2000); // Wait 2 seconds before next reading
  }

  if (gasDetected) {
    digitalWrite(relayPin, LOW);  // Keep relay OFF
    // Add these lines to stop the fan
    //digitalWrite(IN1, LOW);
    //digitalWrite(IN2, LOW);
    //analogWrite(ENA, 0);
    digitalWrite(LED_PIN,LOW);
    tone(buzzerPin, 2000);        // Buzzer keeps beeping continuously


/*
    for (int i = 0; i < 3; i++) {
      tone(buzzerPin, 500);
      delay(100);
      noTone(buzzerPin);
      delay(100);
  }*/

  while (true) {
    tone(buzzerPin, 2000);  // 2000 Hz tone for the beep
    delay(100);             // 100ms delay between beeps
    noTone(buzzerPin);      // Stop the beep
    delay(100);             // 100ms delay before the next beep

    Serial.println("🚨 GAS LEAKAGE DETECTED !| System OFF | Buzzer ON (Manual Reset Required) 🚨");

     // Update LCD display
    lcd.clear();                // Clear the LCD screen
    lcd.setCursor(0, 0);        // Set cursor to the first line
    lcd.print("Gas Leakage Detected !     ");
    lcd.setCursor(0, 1);        // Set cursor to the second line
    lcd.print("System OFF      ");

    // Scroll the first line text
    for (int i = 0; i < 20; i++) {
      lcd.scrollDisplayLeft();
      //delay(100);  // Adjust delay for scroll speed
    } 

    // Clear the LCD after scrolling
    lcd.clear();
    lcd.setCursor(0, 0);        // Set cursor to the first line
    lcd.print("Gas Detected !     ");
    lcd.setCursor(0, 1);        // Set cursor to the second line
    lcd.print("System OFF      ");
  }

  }

  delay(1000);  // Wait 1 second before checking again

      
}

