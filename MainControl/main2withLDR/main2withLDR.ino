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

void setup() {
  Serial.begin(9600); // Start Serial Monitor
  Serial.println("Temperature & LDR-Based Fan and Light Controller Initialized");

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
}

void loop() {
  // Read temperature and humidity from DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read LDR sensor value
  int ldrValue = analogRead(LDR_PIN);

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

