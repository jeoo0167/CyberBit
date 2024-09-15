#include "Pins.h"
#include "Motors.h"

void Motors::Begin(){
  PinSetup& pins = PinSetup::getInstance();
  this->IN1 = pins.IN1;
  this->IN2 = pins.IN2;
  this->IN3 = pins.IN3;
  this->IN4 = pins.IN4;
  this->srv = pins.srv;

  TurnViewServo.attach(this->srv);

  pinMode(this->IN1, OUTPUT);
  pinMode(this->IN2, OUTPUT);  
  pinMode(this->IN3, OUTPUT);
  pinMode(this->IN4, OUTPUT); 
  motors.RotateTo(90);
}

void Motors::moveMotors(int mr1State, int mr2State, int ml1State, int ml2State){
  digitalWrite(this->IN1, mr1State); 
  digitalWrite(this->IN2, mr2State);
  digitalWrite(this->IN3, ml1State);
  digitalWrite(this->IN4, ml2State);
}

void Motors::Forward(){
  moveMotors(HIGH, LOW, HIGH, LOW);
  onStop = false;
}

void Motors::Back(){
  moveMotors(LOW, HIGH, LOW, HIGH);
  onStop = false;
}

void Motors::Left(){
  moveMotors(LOW, HIGH, HIGH, LOW);
  onStop = false;
}

void Motors::Right(){
  moveMotors(HIGH, LOW, LOW, HIGH);
  onStop = false;
}

void Motors::Stop(){
  moveMotors(LOW, LOW, LOW, LOW);
  onStop = true;
}
void Motors::RotateTo(int grade)
{
  TurnViewServo.write(grade);
}
