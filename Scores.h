

#ifndef Scores_H
#define Scores_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

using namespace std;

class Nodo{
    public:
    string jugador;
    int punteo;
    Nodo *siguiente;
    friend class Lista;
    };

class Lista{

  public:
   
  Lista();
  ~Lista();

   void Insertar(string, int);
   void Eliminar(Nodo *&, int);
   void Buscar(Nodo *, int);
   void Mostrar(Nodo *);
   void GraficarGlobal();
   void GraficarIndividual();
  
Nodo *lista;

};



#endif 