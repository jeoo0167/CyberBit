#ifndef Pins_h
#define Pins_h

#include <ESP32Servo.h>

class PinSetup {
  public:
    static PinSetup& getInstance() {
        static PinSetup instance;
        return instance;
    }

    int IN1 = 5;
    int IN2 = 18;
    int IN3 = 19;
    int IN4 = 21;
    int srv = 26;
    Servo TurnViewServo;
    int trig = 13;
    int echo = 12;
    int buzzer = 2;

  private:
    PinSetup() {}
};

#endif
