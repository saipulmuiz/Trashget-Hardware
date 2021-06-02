/*
   Created by Pi BOTS MakerHub

   Email: pibotsmakerhub@gmail.com

   Github: https://github.com/pibotsmakerhub

   Copyright (c) 2020 Pi BOTS MakerHub
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <DHTesp.h>   // Install DHT11 Library and Adafruit Unified Sensor Library


#define FIREBASE_HOST "apesh-app-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "s9wFQlcAlrHFJtA5dnYqaMyQcMLqzZ2jnSBRVFfa"
#define WIFI_SSID "SM-NET+"
#define WIFI_PASSWORD "saipul123258"

#define DHTPIN D1
#define TYPE DHT11
int led = D5;     // Connect LED to D5


DHTesp dht;

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;


void setup()
{

  Serial.begin(9600);

  pinMode(D1, INPUT);
  dht.setup(D1, DHTesp::DHT22);
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
    float temp = dht.getTemperature();
    float humid = dht.getHumidity();
  // Check if any reads failed and exit early (to try again).
  if (isnan(temp) || isnan(humid)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

    Serial.println("------------------------------");
    Serial.println("Set int test...");
    Serial.println(temp);
    Serial.println(humid);

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temperature", temp))
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

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/humidity", humid))
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
  delay(100);
}