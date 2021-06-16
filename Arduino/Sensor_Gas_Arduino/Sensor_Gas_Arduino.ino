#include <MQ2.h>
 
int pinAout = A0;
int lpg_gas, co_gas, smoke_gas;
 
MQ2 mq2(pinAout);
 
void setup(){
  Serial.begin(9600);
  mq2.begin();
}
 
void loop(){
  float* values= mq2.read(true);
  lpg_gas = mq2.readLPG();
  co_gas = mq2.readCO();
  smoke_gas = mq2.readSmoke();
  delay(500);
}
