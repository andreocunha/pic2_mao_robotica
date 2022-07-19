#ifndef __FINGERS_H__
#define __FINGERS_H__

#include <Arduino.h>
#include <Servo.h>


void init_fingers();
//void move_fingers(char* d1, char* d2, char* d3, char* d4, char* d5);
void move_fingers(long d1, long d2, long d3, long d4, long d5);
void finger_teste();

#endif
