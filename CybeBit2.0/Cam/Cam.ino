#include "Networks.h"

Networks netws;

unsigned long lastFrameTime = 0;
const unsigned long frameInterval = 200;

void setup()
{
  Serial.begin(9600);
  netws.Launch();
  
}

void loop()
{
    netws.CleanClients();
    
    unsigned long currentTime = millis();
    if (currentTime - lastFrameTime >= frameInterval) {
        netws.sendFrame();
        lastFrameTime = currentTime;
    }
}
