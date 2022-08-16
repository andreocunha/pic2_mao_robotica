#include "fingers.h"

Servo dedo1; // dedao
Servo dedo2;
Servo dedo3;
Servo dedo4;
Servo dedo5;

void init_fingers(){
  dedo1.attach(D1);
  dedo2.attach(D2);
  dedo3.attach(D3);
  dedo4.attach(D4);
  dedo5.attach(D5);  // anexando o pino D5 do NodeMcu ao meuservo

  // inicializando com 180
  dedo1.write(180);
  dedo2.write(180);
  dedo3.write(180);
  dedo4.write(180);
  dedo5.write(180);

}

static int convert(int percent){
    return (percent*180)/100;
}

void move_fingers(int d1, int d2, int d3, int d4, int d5){
  dedo1.write(convert(d1));
  dedo2.write(convert(d2));
  dedo3.write(convert(d3));
  dedo4.write(convert(d4));
  dedo5.write(convert(d5));
}
