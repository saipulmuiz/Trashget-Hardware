const int flamePin = 7;
int Flame = HIGH;

void setup() 
{
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  Flame = digitalRead(flamePin);
  if (Flame== LOW)
  {
    Serial.println("Fire!!!");
  }
  else
  {
    Serial.println("No worries");
  }
  delay(500);
}
