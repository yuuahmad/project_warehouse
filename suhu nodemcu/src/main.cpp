#include <Arduino.h>

/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 *
 * Copyright (c) 2023 mobizt
 *
 */
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include <Wire.h>
#include <SD.h>
#include <WiFiClientSecure.h>

// include lib service online tealtime clock
#include <NTPClient.h>
// set ntpudp
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

// include lib dht11 dan segala yang berhubungan dengannya
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4 // Pin data sensor DHT11 terhubung ke GPIO 4
DHT dht(DHTPIN, DHT11);
uint32_t delayMS;

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Note"
#define WIFI_PASSWORD "12341234"

/* 1. Define the API Key */
#define API_KEY "AIzaSyBuVMlC_Pbu45KNLdtEvGArcvz7NUFMJO4"
/* 2. Define the RTDB URL */
#define DATABASE_URL "absensi-warehouse-default-rtdb.asia-southeast1.firebasedatabase.app"
/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "yusuf@gmail.com"
#define USER_PASSWORD "11111111"

// Define Firebase Data object
#define FIREBASE_PROJECT_ID "absensi-warehouse"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
unsigned long dataMillis = 0;
unsigned long count = 0; // count untuk menuliskan datake-...?

// variabel untuk sensor dan services
int timestamp;    // buat timestamp untuk menggantikan data rtc
float suhu;       // buat variabel suhu untuk simpan datanya
float kelembapan; // buat variabel kelembapan untuk simpan datanya

void setup()
{

  Serial.begin(115200);

  // inisialisasi module dht yang dipakai
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    if (millis() - ms > 10000)
      break;
#endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
  fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
  // fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;

  // mulai timeclient
  timeClient.begin();
}

void loop()
{
  // delay setiap 2 detik utnuk mendapatkan pembacaan datanya
  delay(2000);

  // baca nilai sensor dht11
  if (isnan(dht.readTemperature()))
  {
    Serial.println(F("Error reading temperature!"));
    suhu = 0;
  }
  else
  {
    Serial.print(F("Temperature: "));
    Serial.print(dht.readTemperature());
    Serial.println(F("°C"));
    suhu = dht.readTemperature();
  }
  // Get humidity event and print its value.
  if (isnan(dht.readHumidity()))
  {
    Serial.println(F("Error reading humidity!"));
    kelembapan = 0;
  }
  else
  {
    Serial.print(F("Humidity: "));
    Serial.print(dht.readHumidity());
    Serial.println(F("%"));
    kelembapan = dht.readHumidity();
  }

  timeClient.update();
  Serial.println(timeClient.getEpochTime());
  timestamp = timeClient.getEpochTime();

  // upload suhu setiap 1 menit sekali
  if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
  {
    dataMillis = millis(); // update milis untuk menampilkan data dan menjalankan algoritma upload data

    FirebaseJson content;
    String documentPath = "sensors/" + String(timestamp);

    content.set("fields/suhu/doubleValue", suhu);
    content.set("fields/waktuUpload/integerValue", timestamp);
    content.set("fields/kelembapan/doubleValue", kelembapan);
    Serial.print("Create a document... ");

    if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
      Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
    else
      Serial.println(fbdo.errorReason());
  }
}
