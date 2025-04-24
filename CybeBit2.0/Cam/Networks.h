#ifndef NETWORKS_H
#define NETWORKS_H

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <SPIFFS.h>
#include "CamSetup.h"
#include "Config.h"

class Networks {
  public:
      void Launch();
      void notFound(AsyncWebServerRequest *request);
      void GetRequest(const String& message);
      void sendFrame();
      void SendData(int Data);
      void Server_Init();
      void CleanClients();
  
  private:
      AsyncWebServer server{80};
      AsyncWebSocket ws{"/ws"};
      CamSetup cam_setup;
};

#endif
