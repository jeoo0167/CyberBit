#ifndef CONFIG_H
#define CONFIG_H

#include <esp_camera.h>

class Confs {
  public:
    static Confs& getInstance() {
        static Confs instance;
        return instance;
    }

  uint8_t i2C_ADDRESS = 0x08;
    
  const char* ssid = "cyberbit";
  const char* password = "12345678";
  
  int scl = 15;
  int sda = 14;

  int pin_d0 = 5;
  int pin_d1 = 18;
  int pin_d2 = 19;
  int pin_d3 = 21;
  int pin_d4 = 36;
  int pin_d5 = 39;
  int pin_d6 = 34;
  int pin_d7 = 35;
  int pin_xclk = 0;
  int pin_pclk = 22;
  int pin_vsync = 25;
  int pin_href = 23;
  int pin_sccb_sda = 26;
  int pin_sccb_scl = 27;
  int pin_pwdn = 32;
  int pin_reset = -1;
  int xclk_freq_hz = 20000000;
  pixformat_t pixel_format = PIXFORMAT_JPEG;
  
  private:
    Confs() {}
};

#endif
