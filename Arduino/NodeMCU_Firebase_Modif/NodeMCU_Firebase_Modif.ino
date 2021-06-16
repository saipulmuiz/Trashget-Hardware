#include "FirebaseESP8266.h"
#include <MQ2.h>

// Define Ultrasonik
#define trigPin D0
#define echoPin D1
#define trigPin2 D2
#define echoPin2 D3
int maximumRange = 100; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long duration, duration2, distance, distance2, capacity, capacity2, overallCapacity; //waktu untuk kalkulasi jarak

// Define Flame Sensor
#define flameSensor D4
int Flame = HIGH;
boolean isFire = false;

// Define Gas Sensor
#define gasSensor A0
int co_gas;
MQ2 mq2(gasSensor);

// Define LED
#define ledRed D5
#define ledYellow D6
#define ledGreen D7

//Define FirebaseESP8266 data object
#define FIREBASE_HOST "apesh-app-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "s9wFQlcAlrHFJtA5dnYqaMyQcMLqzZ2jnSBRVFfa"
#define WIFI_SSID "FoXiFi"
#define WIFI_PASSWORD "saipul123258"
String PATH_IOT = "/FirebaseIOT";
FirebaseData firebaseData;

void setup()
{
  Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  // Ultrasonik Init
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Flame Sensor Init
  pinMode(flameSensor, INPUT);

  // Gas Sensor Init
  mq2.begin();

  // Firebase WiFi Init
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void readSensor() {
  // Ultrasonik 1 Loop
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58.2;
  capacity = (distance * 100) / maximumRange;

  // Ultrasonik 2 Loop
  digitalWrite(trigPin2, LOW); delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);

  distance2 = duration2 / 58.2;
  capacity2 = (distance2 * 100) / maximumRange;

  float* values = mq2.read(true);
  co_gas = mq2.readCO();;

  Flame = digitalRead(flameSensor);
  if (isnan(duration) || isnan(duration2) || isnan(Flame)) {
    Serial.println(F("Failed to read from sensor!"));
    return;
  }

  if (Flame == LOW) {
    Firebase.setBool(firebaseData, PATH_IOT + "/fire", true);
    Serial.println("Api Terdeteksi! ");
  } else {
    Firebase.setBool(firebaseData, PATH_IOT + "/fire", false);
    Firebase.setFloat(firebaseData, PATH_IOT + "/organicCapacity", capacity);
    Firebase.setFloat(firebaseData, PATH_IOT + "/anorganicCapacity", capacity2);
    Firebase.setFloat(firebaseData, PATH_IOT + "/kadarGas", co_gas);
    Serial.println("------------------------------");
    Serial.println("Set int test...");
    Serial.print(distance); Serial.println(" cm - 1");
    Serial.print(capacity); Serial.println(" %");
    Serial.print(distance2); Serial.println(" cm - 2");
    Serial.print(capacity2); Serial.println(" %");
    Serial.print(co_gas); Serial.println(" ppm");
    overallCapacity = (capacity + capacity2) / 2;
    if (overallCapacity >= 0 && overallCapacity < 50) {
      isGreenLed();
    } else if (overallCapacity > 50 && overallCapacity < 80) {
      isYellowLed();
    } else if (overallCapacity > 80) {
      isRedLed();
    }
  }
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
  readSensor();
  delay(1000);
}
