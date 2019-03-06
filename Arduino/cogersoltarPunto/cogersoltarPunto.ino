#include "Braccio.h"
#include "Punto.h"
#include <stdio.h>
#include <stdlib.h>

String bentrada;
Punto p1,p2;
int i;
byte bentradaB[50];

void setup(){
  Braccio.begin();
  Serial.begin(9600);
  i = 0;
}

void loop(){
  i = 0;
  if(Serial.available()>0){
    Serial.readBytes(bentradaB, 50);
    
    bentrada = String((char*)bentradaB);
    
    p1 = Punto(bentrada, i);
    p2 = Punto(bentrada, i);
    
    p1 > p2;
  }
}
