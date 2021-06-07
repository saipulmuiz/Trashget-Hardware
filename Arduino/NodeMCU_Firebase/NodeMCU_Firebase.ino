#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library

int led = D5;     // Connect LED to D5

// Define Ultrasonik
#define trigPin D0 //Trigger Pin
#define echoPin D1 //Echo Pin
int maximumRange = 100; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long duration, distance, capacity; //waktu untuk kalkulasi jarak

// Define Flame Sensor
#define flameSensor D3
int Flame = HIGH;
boolean isFire = false;

//Define FirebaseESP8266 data object
#define FIREBASE_HOST "apesh-app-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "s9wFQlcAlrHFJtA5dnYqaMyQcMLqzZ2jnSBRVFfa"
#define WIFI_SSID "SM-NET+"
#define WIFI_PASSWORD "saipul123258"
FirebaseData firebaseData;
FirebaseData ledData;
FirebaseJson json;

void setup()
{
  Serial.begin(9600);

  pinMode(led, OUTPUT);

  // Ultrasonik Init
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Flame Sensor Init
  pinMode(flameSensor, INPUT);
  
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

void sensorUltrasonik() {
  // Ultrasonik Loop
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration / 58.2;
  capacity = (distance * 100) / maximumRange;

  Flame = digitalRead(flameSensor);
  if (isnan(duration) || isnan(Flame)) {
    Serial.println(F("Failed to read from sensor!"));
    return;
  }
  if (Flame == LOW) {
    Firebase.setBool(firebaseData, "/FirebaseIOT/fire", true);
//    if (Firebase.setBool(firebaseData, "/FirebaseIOT/fire", true))
//    {
//        Serial.println("PASSED");
//        Serial.println("PATH: " + firebaseData.dataPath());
//        Serial.println("TYPE: " + firebaseData.dataType());
//        Serial.println("ETag: " + firebaseData.ETag());
//        Serial.println("------------------------------------");
//        Serial.println();
//    }
//    else
//    {
//        Serial.println("FAILED");
//        Serial.println("REASON: " + firebaseData.errorReason());
//        Serial.println("---------------------------------");
//        Serial.println("FAILED");
//    }
    Serial.println("Api Terdeteksi! ");
  } else {
    Firebase.setBool(firebaseData, "/FirebaseIOT/fire", false);
    Firebase.setFloat(firebaseData, "/FirebaseIOT/capacity", distance);
    Serial.println("------------------------------");
    Serial.println("Set int test...");
    Serial.print(distance); Serial.println(" cm");
    Serial.print(capacity); Serial.println(" %");
//    if (Firebase.setFloat(firebaseData, "/FirebaseIOT/capacity", distance))
//    {
//        Serial.println("PASSED");
//        Serial.println("PATH: " + firebaseData.dataPath());
//        Serial.println("TYPE: " + firebaseData.dataType());
//        Serial.println("ETag: " + firebaseData.ETag());
//        Serial.println("------------------------------------");
//        Serial.println();
//    }
//    else
//    {
//        Serial.println("FAILED");
//        Serial.println("REASON: " + firebaseData.errorReason());
//        Serial.println("---------------------------------");
//        Serial.println("FAILED");
//    }
  }
  
//  Serial.print("Gas Metan : "); Serial.println(CH4);
}

void sensorFlame() {
  // Flame Sensor Loop
  Flame = digitalRead(flameSensor);
  if (isnan(Flame)) {
    Serial.println(F("Failed to read from Flame sensor!"));
    return;
  }
  if (Flame == LOW) {
    isFire = true;
  } else {
    isFire = false;
  }
  Serial.print("Api : "); Serial.println(isFire);
//  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/fire", isFire))
//    {
//        Serial.println("PASSED");
//        Serial.println("PATH: " + firebaseData.dataPath());
//        Serial.println("TYPE: " + firebaseData.dataType());
//        Serial.println("ETag: " + firebaseData.ETag());
//        Serial.println("------------------------------------");
//        Serial.println();
//    }
//  else
//    {
//        Serial.println("FAILED");
//        Serial.println("REASON: " + firebaseData.errorReason());
//        Serial.println("---------------------------------");
//        Serial.println("FAILED");
//    }
}
void loop() {
  sensorUltrasonik();
//  sensorFlame();

//  if (Firebase.getString(ledData, "/FirebaseIOT/led")) {
//    Serial.println(ledData.stringData());
//    if (ledData.stringData() == "1") {
//      digitalWrite(led, HIGH);
//    }
//    else if (ledData.stringData() == "0") {
//      digitalWrite(led, LOW);
//    }
//  }
  delay(500);
}
