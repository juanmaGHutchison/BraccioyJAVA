#include "Punto.h"

const int Punto::tablero2x3a7cm[2][3][5] = {{{85,95,0,45,90},{55,90,7,42,90},{120,95,0,53,90}},{{81,68,30,46,90},{60,65,33,45,90},{109,66,33,46,90}}};

//Constructores
Punto::Punto(int x, int y):x_(x),y_(y){}
Punto::Punto(String str, int& i){
  String auxX,auxY;
  x_ = 1;
  y_ = 1;
  ++i;
  if(str[i] == '-'){
    x_ = -1;
    ++i;
  }
  while(str[i] != ','){
    if(!(str[i] == ',' || str[i] == '(' || str[i] == ')'))
      auxX += str[i];
    ++i;
  }
  ++i;
  if(str[i] == '-'){
    y_ = -1;
    ++i;
  }
  while(str[i] != ')'){
     if(!(str[i] == ',' || str[i] == '(' || str[i] == ')'))
      auxY += str[i];
     ++i;
  }
  ++i;
  
  x_ *= auxX.toInt();
  y_ *= auxY.toInt();
}

//Observadores
int Punto::x()const{return x_;}
int Punto::y()const{return y_;}

//Modificadores
int& Punto::x(){return x_;}
int& Punto::y(){return y_;}

void Punto::x(int px){x_ = px;}
void Punto::y(int py){y_ = py;}

//Incremento o decremento
Punto& Punto::incrementaX(int incremento){
	x_ += incremento;
	
    static const int tablero2x3a7cm[2][3][5] = {{{90,95,0,45,90},{62,90,30,45,90},{125,95,0,50,90}},{{93,68,30,46,90},{70,65,33,46,90},{115,66,33,48,90}}};
	
	return *this;
}
Punto& Punto::decrementaX(int decremento){
	x_ -= decremento;
 
	return *this;	
}

Punto& Punto::incrementaY(int incremento){
	y_ += incremento;
 
	return *this;
}
Punto& Punto::decrementaY(int decremento){
	y_ -= decremento;
	
	return *this;
}

//convertir Punto a cadena caracteres bajo nivel
const char* Punto::cadena()const{
		static char punto[10];
		
		sprintf(punto, "(%d,%d)", x_, y_);
		
		return punto;
}

//TRANSPORTAR OBJETO
void operator >(const Punto& p1, const Punto& p2){
  Braccio.soltar();
  delay(1000);
	p1.ejecutar();
  delay(1000);
  Braccio.agarrar();
  Braccio.M3(90);
  delay(2000);
  p2.ejecutar();
  delay(1000);
  Braccio.soltar();
  delay(1000);
  Braccio.ServoMovement(10, 90, 90, 90, 90, 90, 10);
}

void operator <(const Punto& p1, const Punto& p2){
	p2 > p1;
}

//SUMA Y RESTA
Punto operator + (const Punto& p1, const Punto& p2){
	return Punto(p1.x()+p2.x(), p1.y()+p2.y());
}

Punto operator - (const Punto& p1, const Punto& p2){
	return Punto(p1.x()-p2.x(), p1.y()-p2.y());
}

void Punto::ejecutar(){
  if(y_ == -1) y_ = 2;
  Braccio.M1(tablero2x3a7cm[x_][y_][0]);
  Braccio.M4(tablero2x3a7cm[x_][y_][3]);
  Braccio.M5(tablero2x3a7cm[x_][y_][4]);
  if(x_ == 0){
    Braccio.M2(tablero2x3a7cm[x_][y_][1]);
    Braccio.M3(tablero2x3a7cm[x_][y_][2]);
  }else{
    Braccio.M3(tablero2x3a7cm[x_][y_][2]);
    Braccio.M2(tablero2x3a7cm[x_][y_][1]);
  }
}
