int Gas_analog = A0;    // used for ESP32
int Gas_digital = 7;   // used for ESP32

void setup() {
  Serial.begin(115200);
  pinMode(Gas_digital, INPUT);
}

void loop() {
  int gassensorAnalog = analogRead(Gas_analog);
  int gassensorDigital = digitalRead(Gas_digital);

  Serial.print("Gas Sensor: ");
  Serial.println(gassensorAnalog);
  Serial.print("Gas Class: ");
  Serial.println(gassensorDigital);
  delay(500);
}
