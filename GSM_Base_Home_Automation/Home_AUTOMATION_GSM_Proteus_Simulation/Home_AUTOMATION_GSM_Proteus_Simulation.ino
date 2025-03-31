#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6,7);
const int fan_pin = 8;
const int bulb_pin = 9;
const int buzzer = 10;
String gsm_read = "";
void RecieveMessage();

void setup()
{
  Serial.begin(9600);
  pinMode(fan_pin, OUTPUT);
  pinMode(bulb_pin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("In Setup ...");
  delay(100);
  lcd.begin(16, 2);
  lcd.print("GSM Base");
  lcd.setCursor(0,2);
  lcd.print("Home Automation");
  delay(1000);
  RecieveMessage();
}

void loop()
{
   lcd.clear();
   lcd.print("Waiting for ");
   lcd.setCursor(0,2);
   lcd.print("command");
   delay(100);
    while (Serial.available() > 0)
    {
      gsm_read= Serial.readString();
      gsm_read.remove(gsm_read.length()-1);
      if(gsm_read == "FAN_ON")
      {
          lcd.clear();
          lcd.print("motor On");
          delay(100);
           digitalWrite(fan_pin, HIGH); 
          delay(100);
      }
      else if(gsm_read == "FAN_OFF")
      {
          lcd.clear();
          lcd.print("motor OFF");
          delay(100);
          digitalWrite(fan_pin, LOW); 
          delay(100);
      }
      else if(gsm_read == "BULB_ON")
      {
          lcd.clear();
          lcd.print("BULB ON");
          delay(100);
          digitalWrite(bulb_pin, HIGH); 
          delay(100);
      }
      else if(gsm_read == "BULB_OFF")
      {
          lcd.clear();
          lcd.print("BULB OFF");
          delay(100);
          digitalWrite(bulb_pin, LOW); 
          delay(100);
      }
      else
      {
        lcd.clear();
        lcd.print("wrong password");
        delay(100);
        digitalWrite(buzzer, HIGH); 
        delay(500);
        digitalWrite(buzzer, LOW); 
        delay(100);
      }
    }
}


void RecieveMessage()
{
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CNMI = 2,2,0,0,0");
  delay(1000);
}
