#include "CamSetup.h"
#include <esp_camera.h>
#include <esp_system.h>
#include <esp_psram.h>
#include <Arduino.h>
void CamSetup::Setup()
{
  Confs& confs = Confs::getInstance();
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = confs.pin_d0;
  config.pin_d1 = confs.pin_d1;
  config.pin_d2 = confs.pin_d2;
  config.pin_d3 = confs.pin_d3;
  config.pin_d4 = confs.pin_d4;
  config.pin_d5 = confs.pin_d5;
  config.pin_d6 = confs.pin_d6;
  config.pin_d7 = confs.pin_d7;
  config.pin_xclk = confs.pin_xclk;
  config.pin_pclk = confs.pin_pclk;
  config.pin_vsync = confs.pin_vsync;
  config.pin_href = confs.pin_href;
  config.pin_sccb_sda = confs.pin_sccb_sda;
  config.pin_sccb_scl = confs.pin_sccb_scl;
  config.pin_pwdn = confs.pin_pwdn;
  config.pin_reset = confs.pin_reset;
  config.xclk_freq_hz = confs.xclk_freq_hz;
  config.pixel_format = confs.pixel_format;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  if (esp_camera_init(&config) != ESP_OK) {
      return;
  }
}
