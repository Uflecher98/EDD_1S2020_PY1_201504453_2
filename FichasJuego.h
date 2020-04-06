

#ifndef FICHASJUEGO_H
#define FICHASJUEGO_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <stdio.h>

using namespace std;

class NodoD{
    public:
    int id;
    int valor;
    char letra;
    string ide;
    NodoD *siguiente;
    NodoD *anterior;
   };

class Doble{

  public:
   
  Doble();
  ~Doble();

   void Insertar(int id, int valor, char letra);
   NodoD * Eliminar(char letra);
   void Modificar(int, int, int, char);
   void Graficar(string usuario);
   void Mostrar();
   void Vaciar();
  
  
 NodoD *primero;
 NodoD *ultimo;

};



#endif 

  
