

#ifndef Fichas_H
#define Fichas_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"FichasJuego.h"
using namespace std;

/*
class NodoCola{
    public:
    int id;
    int valor;
    char letra;
    NodoCola *siguiente;

    }; */

class Cola{

  public:
   
  Cola();
  ~Cola();

   void Insertar(int id, int valor, char letra);
   void Graficar();
   bool Cola_Vacia(NodoD *);
   NodoD * Eliminar();
   void Vaciar();
   int contar();
  
 NodoD *frente;
 NodoD *fin;

};



#endif 