#include "Motors.h"
#include "Pins.h"
#include "webControll.h"
#include "Sound.h"

Motors motors;
Networking networking;
Sounds sound;

// Definición de variables globales
unsigned long startTime = 0;
const unsigned long timeout = 300000;  

void setup() {
  Serial.begin(115200);
  sound.StartSound();
  delay(2000);
  motors.Begin();
  networking.Begin();
  Serial.println("Sistema iniciado.");
  startTime = millis();
  
}

void loop() {
  networking.ws.cleanupClients();

  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  if (motors.onStop == true) {
    int remainingSeconds = (timeout - elapsedTime) / 1000;
    if (remainingSeconds < 0) remainingSeconds = 0;
    Serial.println(remainingSeconds);

    if (elapsedTime >= timeout) {
      sound.Bored();
      delay(2000);
      esp_deep_sleep_start();
    }
    
    delay(1000);
  } else {
    startTime = millis();
  }
}
