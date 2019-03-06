#ifndef PUNTO_HPP_
#define PUNTO_HPP_

#include "stdio.h"
#include "Braccio.h"
#include <Arduino.h>
#include <Servo.h>

class Punto{
	public:
		//Constantes
		static const int MaximoX = 1, MaximoY = 1;
		
		//Constructores
		Punto(int=0, int=0);
    Punto(String, int&);
		
		//Observadores
		int x()const;
		int y()const;
		
		//Modificadores
		int& x();
		int& y();
		
		void x(int);
		void y(int);
		
		//Incremento o decremento
		Punto& incrementaX(int = 1);
		Punto& decrementaX(int = 1);
		
		Punto& incrementaY(int = 1);
		Punto& decrementaY(int = 1);
		
		//convertir Punto a cadena caracteres bajo nivel
		const char* cadena()const;

    //EJECUTAR
    void ejecutar();
		
	private:
		int x_, y_;
    
    static const int tablero2x3a7cm[2][3][5];
};

//TRANSPORTAR OBJETO
void operator > (const Punto&, const Punto&);
void operator < (const Punto&, const Punto&);

//SUMA Y RESTA
Punto operator + (const Punto&, const Punto&);
Punto operator - (const Punto&, const Punto&);

#endif
