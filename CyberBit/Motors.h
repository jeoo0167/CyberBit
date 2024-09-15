#ifndef Motors_h
#define Motors_h

#include "Pins.h"

class Motors{
  public:
    bool onStop = false;
    void moveMotors(int mr1State, int mr2State, int ml1State, int ml2State);
    void Begin();
    void Forward();
    void Back();
    void Left();
    void Right();
    void Stop();
    void RotateTo(int grades);
  
  private:
    int IN1; 
    int IN2;
    int IN3;
    int IN4;
    int srv;
    Servo TurnViewServo;
};
extern Motors motors;
#endif
