//IO sensor 1
#define echoPin 11 //Echo Pin
#define trigPin 12 //Trigger Pin
 
int maximumRange = 100; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long duration, distance; //waktu untuk kalkulasi jarak
int capacity;
 
void setup() {
Serial.begin (9600); //inisialiasasi komunikasi serial
//deklarasi pin
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
 
void loop() {
digitalWrite(trigPin, LOW);delayMicroseconds(2);
digitalWrite(trigPin, HIGH);delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
 
//perhitungan untuk dijadikan jarak
distance = duration/58.2;
capacity = (distance * 100) / maximumRange;
Serial.print(distance);Serial.println(" cm");
Serial.print(capacity);Serial.println(" %");
delay(1000);
}
