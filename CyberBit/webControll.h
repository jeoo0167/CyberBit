#ifndef Web_Controll_h
#define Web_Controll_h

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

class Networking {
  public:
    // Inicializa la conexión WiFi y el servidor
    void Begin();
    
    // Maneja los eventos del WebSocket
    void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    
    // Respuesta en caso de que no se encuentre la página
    void notFound(AsyncWebServerRequest *request);

    // Acceso público al WebSocket
    AsyncWebSocket ws{"/ws"};
  
  private:
    // Credenciales de la red WiFi
    const char* ssid = "CyberBit-Network";
    const char* password = "CyberBit";
    
    // Instancia del servidor
    AsyncWebServer server{80};
};

#endif
