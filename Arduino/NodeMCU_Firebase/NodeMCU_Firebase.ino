/*
   Created by Pi BOTS MakerHub

   Email: pibotsmakerhub@gmail.com

   Github: https://github.com/pibotsmakerhub

   Copyright (c) 2020 Pi BOTS MakerHub
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
//#include <ESP8266WiFi.h>


#define FIREBASE_HOST "apesh-app-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "s9wFQlcAlrHFJtA5dnYqaMyQcMLqzZ2jnSBRVFfa"
#define WIFI_SSID "SM-NET+"
#define WIFI_PASSWORD "saipul123258"

#define trigPin D0 //Trigger Pin
#define echoPin D1 //Echo Pin
int led = D5;     // Connect LED to D5

int maximumRange = 100; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long duration, distance, capacity; //waktu untuk kalkulasi jarak

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;

void setup()
{

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
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

void sensorUpdate() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // Check if any reads failed and exit early (to try again).
  if (isnan(duration)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  distance = duration / 58.2;
  capacity = (distance * 100) / maximumRange;
  Serial.println("------------------------------");
  Serial.println("Set int test...");
  Serial.print(distance); Serial.println(" cm");
  Serial.print(capacity); Serial.println(" %");

    if (Firebase.setFloat(firebaseData, "/FirebaseIOT/distance", distance))
      {
          Serial.println("PASSED");
          Serial.println("PATH: " + firebaseData.dataPath());
          Serial.println("TYPE: " + firebaseData.dataType());
          Serial.println("ETag: " + firebaseData.ETag());
          Serial.println("------------------------------------");
          Serial.println();
      }
      else
      {
          Serial.println("FAILED");
          Serial.println("REASON: " + firebaseData.errorReason());
          Serial.println("---------------------------------");
          Serial.println("FAILED");
      }
}
void loop() {
  sensorUpdate();

  if (Firebase.getString(ledData, "/FirebaseIOT/led")) {
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
      digitalWrite(led, HIGH);
    }
    else if (ledData.stringData() == "0") {
      digitalWrite(led, LOW);
    }
  }
  delay(1000);
}
