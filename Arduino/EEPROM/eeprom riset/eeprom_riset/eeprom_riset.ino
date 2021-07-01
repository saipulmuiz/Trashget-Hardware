#include <EEPROM.h>

int address = 1;
int tinggi = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print(address);Serial.print("\t");
  Serial.print(tinggi);Serial.println();
  Serial.print("--------------------------------- \n");
}

void loop()
{
  tinggi++;
  EEPROM.write(address, tinggi);
  int val = EEPROM.read(address);
  Serial.print(address);Serial.print("\t");
  Serial.print(val);Serial.println();
  delay(1000);
}
