#ifndef __FINGERS_H__
#define __FINGERS_H__

#include <Arduino.h>
#include <Servo.h>


void init_fingers();
void move_fingers(int d1, int d2, int d3, int d4, int d5);

#endif
