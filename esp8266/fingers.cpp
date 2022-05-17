#include "fingers.h"

void init_fingers(){
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
}

void move_fingers(char* d1, char* d2, char* d3, char* d4, char* d5){
//  Serial.printf("%s\n", fingers['info']);
  
  d1 == (char*)'1' ? digitalWrite(D1, HIGH) : digitalWrite(D1, LOW);
  d2 == (char*)'1' ? digitalWrite(D2, HIGH) : digitalWrite(D2, LOW);
  d3 == (char*)'1' ? digitalWrite(D3, HIGH) : digitalWrite(D3, LOW);
  d4 == (char*)'1' ? digitalWrite(D4, HIGH) : digitalWrite(D4, LOW);
  d5 == (char*)'1' ? digitalWrite(D5, HIGH) : digitalWrite(D5, LOW);
}
