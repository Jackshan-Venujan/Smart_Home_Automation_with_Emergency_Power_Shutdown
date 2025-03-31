#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Ensure the correct I2C address

void setup() 
{
  lcd.init();  // Use init() instead of begin()
  lcd.backlight(); // Turn on the backlight
  lcd.clear();
}

void loop() 
{
  lcd.setCursor(4, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("I2C LCD Project");
  delay(2000); // Add a delay to avoid flickering
}

