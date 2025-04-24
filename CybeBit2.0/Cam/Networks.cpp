#include "Networks.h"

void Networks::Server_Init()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html", "text/html");
  });
  
  ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
      if (type == WS_EVT_DATA) {
          String message = "";
          for (size_t i = 0; i < len; i++) {
              message += (char)data[i];
          }
          GetRequest(message);
      }
  }); 
   
  server.addHandler(&ws);
  server.begin();
}

void Networks::Launch()
{
  Confs& confs = Confs::getInstance();
  cam_setup.Setup();
  Wire.begin(confs.scl,confs.sda);
  WiFi.softAP(confs.ssid,confs.password);
  if (!SPIFFS.begin(true)) {
    Serial.println("ERROR AL INICIAR SPIFFS");
    return;
  }
  Server_Init();
}

void Networks::GetRequest(const String& message)
{
  if (!message.isEmpty()) 
  {
      if (message.startsWith("Flash:")) 
      {
          int sliderValue = message.substring(6).toInt();
          analogWrite(4, sliderValue);
      } 
      else 
      {
          if (message == "F") {
              SendData(1);
          } else if (message == "B") {
              SendData(2);
          } else if (message == "R") {
              SendData(3);
          } else if (message == "L") {
              SendData(4);
          }else if (message == "Sh"){
              SendData(5);
          } else if (message == "S") {
              SendData(0);
          }
      }
  }
}

void Networks::sendFrame()
{
    if (ws.count() == 0) return;

    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Error al capturar el frame");
        return;
    }

    ws.binaryAll((uint8_t*)fb->buf, fb->len);
    esp_camera_fb_return(fb);
}

void Networks::CleanClients()
{
  ws.cleanupClients();
}

void Networks::SendData(int Data)
{
  Confs& confs = Confs::getInstance();
  Wire.beginTransmission(confs.i2C_ADDRESS);
  Wire.write(Data);
  Wire.endTransmission(); 
}

void Networks::notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/html", "<h1>Error 404 no se encuentra la pagina</h1>");
}
