// Define LED
#define ledRed 8
#define ledYellow 9
#define ledGreen 10

void setup()
{
  Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void isRedLed() {
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
}

void isYellowLed() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, LOW);
}

void isGreenLed() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, HIGH);
}

void loop() {
  isRedLed();
  delay(1000);
  isYellowLed();
  delay(1000);
  isGreenLed();
  delay(1000);
}
