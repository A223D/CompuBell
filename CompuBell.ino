#include <WiFi.h>
#include <WiFiMulti.h>
#include "FirebaseESP32.h"
#include <Tone32.h>

#define BUZZER_PIN 32
#define BUZZER_CHANNEL 0

FirebaseData firebaseData;

WiFiMulti WiFiMulti;
int ledPin = 2;      // select the pin for the LED
bool count = false;
const char* ssid     = "Don t Dare to Click 2.4";
const char* password = "Kushagra12345";
#define FIREBASE_HOST "https://compubell-8cfcb-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "zwxheKFxzueOpC1fVIdOrmsZv1tJbW8YtuapkIQh"
static bool hasWifi = false;


void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(35, INPUT);
  Serial.begin(9600);
  Serial.println("Connecting to Wifi");
  Serial.println("Connecting...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  hasWifi = true;
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}

void loop() {

  if (digitalRead(35)) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Pressed");

    count = !count;
    tone(BUZZER_PIN, NOTE_C4, 250, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    tone(BUZZER_PIN, NOTE_E4, 250, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    tone(BUZZER_PIN, NOTE_G4, 250, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    tone(BUZZER_PIN, NOTE_C5, 250, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    Firebase.setInt(firebaseData, "/value", count);

  } else {
    digitalWrite(ledPin, LOW);
  }
}
