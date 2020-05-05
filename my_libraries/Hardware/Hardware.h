#ifndef HARDWARE_H
#define HARDWARE_H
#include <Arduino.h>
int buttons();
int distance();
void LEDsDriver (bool LEDs[]);
void MotorDriver ( String motion);
#endif
