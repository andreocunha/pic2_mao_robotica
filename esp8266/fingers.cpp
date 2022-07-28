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

static int convert(long percent){
    return (percent*180)/100;
}

void move_fingers(long d1, long d2, long d3, long d4, long d5){
//  Serial.printf("%s\n", fingers['info']);

  dedo1.write(convert(d1));
  dedo2.write(convert(d2));
  dedo3.write(convert(d3));
  dedo4.write(convert(d4));
  dedo5.write(convert(d5));

//  d2 == (char*)'1' ? dedo2.write(179) : dedo2.write(0);
//  d3 == (char*)'1' ? dedo3.write(179) : dedo3.write(0);
//  d4 == (char*)'1' ? dedo4.write(179) : dedo4.write(0);
//  d5 == (char*)'1' ? dedo5.write(179) : dedo5.write(0);
}


int pos = 0;    // variável de posição iniciada em zero

void finger_teste(){
  for (pos = 0; pos <= 180; pos += 1) { // movimento de 0 a 180º
    // crescente
    dedo4.write(pos);              // escreve posicao em meuservo
    delay(5);                       // aguarda 35ms
  }
  for (pos = 180; pos >= 0; pos -= 1) { // movimento de 180º a 0
    // descrescente
    dedo4.write(pos);              // escreve posicao em meuservo
    delay(5);                       // aguarda 35ms
  }
}
