#include <DHT.h>  // Include the DHT sensor library

#define DHTPIN 2        // Pin where the DHT11 is connected
#define DHTTYPE DHT11   // Define the sensor type (DHT11)
#define LED_PIN 13      // Pin where the LED is connected

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor

void setup() {
  Serial.begin(9600);   // Start serial communication at 9600 baud rate
  dht.begin();          // Initialize the DHT sensor
  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature as Celsius
  float temperature = dht.readTemperature();

  // Check if the reading failed and exit early (NaN = Not a Number)
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the temperature to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Control LED based on temperature
  if (temperature > 30.0) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED on
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn LED off
  }
}

