//YouTube | Tech at Home

int ldr = 7;
int x;
int led = 13;

void setup() 
{
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  x = digitalRead(7);
  Serial.println(x);

  if(x == HIGH)
  {
    digitalWrite(13, HIGH);
  }
  if(x == LOW)
  {
    digitalWrite(13, LOW);
  }

}
