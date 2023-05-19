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

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// include lib modul2 yang digunakan
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>
#include <NTPClient.h>
RFID rfid(D8, D0);                  // D10:pin of tag reader SDA. D9:pin of tag reader RST
unsigned char str[MAX_LEN];         // MAX_LEN is 16: size of the array
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
// set ntpudp
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

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

bool upload = false; // apakah keadaan upload benar atau salah
String idrfid = "";  // menampung data pembacaan rfid
int timestamp;       // buat timestamp untuk menggantikan data rtc

void setup()
{

    Serial.begin(115200);

    // inisialisasi semua module yang dipakai
    lcd.init(); // initialize the lcd
    lcd.clear();
    lcd.backlight();

    SPI.begin();
    rfid.init();

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
    timeClient.update();
    Serial.println(timeClient.getEpochTime());
    timestamp = timeClient.getEpochTime();
    // kode rfid
    if (rfid.findCard(PICC_REQIDL, str) == MI_OK) // Wait for a tag to be placed near the reader
    {
        lcd.setCursor(0, 0);
        lcd.print("detected           ");
        Serial.println("Card found"); // idrfidorary variable to store the read RFID number
        upload = true;
        if (rfid.anticoll(str) == MI_OK) // Anti-collision detection, read tag serial number
        {
            Serial.print("The card's ID number is : ");
            for (int i = 0; i < 4; i++) // Record and display the tag serial number
            {
                idrfid = idrfid + (0x0F & (str[i] >> 4));
                idrfid = idrfid + (0x0F & str[i]);
            }
            Serial.println(idrfid);
            lcd.setCursor(0, 1);
            lcd.print(idrfid);
            lcd.print("         ");
            // checkAccess(idrfid); // Check if the identified tag is an allowed to open tag
        }
        rfid.selectTag(str); // Lock card to prevent a redundant read, removing the line will make the sketch read cards continually
    }
    rfid.halt();

    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("SCAN YOUR RFID    ");
    lcd.setCursor(0, 1);
    lcd.print("input brng        ");

    if (Firebase.ready() && (millis() - dataMillis > 10000 || dataMillis == 0) && upload == true)
    {
        dataMillis = millis(); // update milis untuk menampilkan data dan menjalankan algoritma upload data
        upload = false;

        FirebaseJson content;
        String documentPath = "warehouses/" + String(idrfid);

        content.set("fields/done/booleanValue", false);
        content.set("fields/content/stringValue", idrfid);
        content.set("fields/date/integerValue", 123);
        content.set("fields/jenisBarang/stringValue", "isi data");
        content.set("fields/kelompokTani/stringValue", "isi data");
        content.set("fields/berat/integerValue", 123);
        content.set("fields/waktuScan/integerValue", timestamp);

        count++;

        Serial.print("Create a document... ");

        if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
        {
            idrfid = "";
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        }
        else
        {
            idrfid = "";
            Serial.println(fbdo.errorReason());
        }
    }
}
