#include "Sound.h"
#include "Pins.h"

void Sounds::StartSound(){
  PinSetup& pins = PinSetup::getInstance();
  this->bz = pins.buzzer;
  pinMode(this->bz,OUTPUT);
  for (int i = 0; i <= 35; i++) {
    int frequency = 100 + pow(i, 2) * 0.5;
    tone(bz, frequency);
    delay(25);
  }
  noTone(bz);
  delay(2000); 
}
void Sounds::Sound1()
{
  
}

void Sounds::Bored(){
  tone(bz, 300);
  delay(250);
  tone(bz, 100);
  delay(300);
  noTone(bz);
}
