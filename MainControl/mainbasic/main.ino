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

void setup() {
  Serial.begin(9600); // Start Serial Monitor
  Serial.println("Temperature-Based Fan Controller Initialized");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Fan Controller");

  // Initialize DHT sensor
  dht.begin();

  // Set motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Ensure fan is off initially
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void loop() {
  // Read temperature from DHT11
  float temperature = dht.readTemperature();

  // Check if the reading is valid
  if (isnan(temperature)) {
    Serial.println("Error: Failed to read from DHT11 sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Temp Error!      ");
  } else {
    // Print temperature on LCD and Serial Monitor
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C   ");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

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

    // Print fan status on LCD
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: ");
    lcd.print(fanSpeed);

    // Control motor driver (fan)
    if (fanSpeed > 0) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    }

    analogWrite(ENA, fanSpeed); // Set speed

    // Print fan status on Serial Monitor
    Serial.print("Fan Speed: ");
    Serial.println(fanSpeed);
  }

  delay(2000); // Wait 2 seconds before next reading
}
