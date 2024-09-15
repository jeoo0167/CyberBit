#include "Motors.h"
#include "Pins.h"
#include "webControll.h"
#include <WiFi.h>

void Networking::Begin() {
   if (!SPIFFS.begin(true)) {
    Serial.println("ERROR AL INICIAR SPIFFS");
    return;
  }

  // Configuración del punto de acceso
  WiFi.softAP(ssid, password);
  Serial.println("IP del punto de acceso: " + WiFi.softAPIP().toString());

  // Configura el WebSocket
  ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    this->onWebSocketEvent(server, client, type, arg, data, len);
  });
  
  // Añade el WebSocket al servidor
  server.addHandler(&ws);

  // Sirve el archivo index.html desde SPIFFS
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Página no encontrada
  server.onNotFound([this](AsyncWebServerRequest *request) {
    this->notFound(request);
  });

  // Inicia el servidor
  server.begin();
}

void Networking::onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    String message = "";
    for (size_t i = 0; i < len; i++) {
      message += (char)data[i];
    }

    if (!message.isEmpty()) {
      if (message.startsWith("Servo:")) {
        int sliderValue = message.substring(6).toInt();  // Extrae el valor después de "Servo:"
        motors.RotateTo(sliderValue);  // Usa el servo de la clase Motors
      } else {
        motors.Stop();  // Detiene los motores antes de cambiar de dirección
        if (message == "F") {
          motors.Forward();
          Serial.println("Forward");
        } else if (message == "B") {
          motors.Back();
          Serial.println("Backward");
        } else if (message == "R") {
          motors.Right();
          Serial.println("Right");
        } else if (message == "L") {
          motors.Left();
          Serial.println("Left");
        } else if (message == "S") {
          motors.Stop();
          Serial.println("Stop");
        }
      }
    }
  }
}

void Networking::notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/html", "Página no encontrada. Visita <a href='https://www.pornhub.com'>Google</a> para más información.");
}
