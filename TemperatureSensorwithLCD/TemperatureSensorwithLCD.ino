#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define LCD (I2C address: 0x27, 16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define DHT sensor
#define DHTPIN 8      // DHT11 connected to digital pin 8
#define DHTTYPE DHT11 // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Start Serial Monitor
  Serial.println("DHT11 Sensor Initialized");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Sensor");

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Read temperature & humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if reading is valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error: Failed to read from DHT11 sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Error reading!");
  } else {
    // Print on LCD
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C ");

    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(humidity);
    lcd.print(" % ");

    // Print on Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  delay(2000); // Wait 2 seconds before next reading
}
