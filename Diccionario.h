#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <stdio.h>

using namespace std;

class Nodo_LD{
    public:
    string palabra;
    int id;
    Nodo_LD *anterior;
    Nodo_LD *siguiente;
    friend class ListaDoble;
    };

class ListaDoble{

  public:
   
   ListaDoble();
   ~ListaDoble();
   void InsertarRef(int, string, int);
   void Insertar(string, int);
   void Eliminar(int);
   void Modificar(int, int, string);   
   void Mostrar();
   bool BuscarNodo(string palabra);
 

   void Graficar();
   

 Nodo_LD *primero;
 Nodo_LD *ultimo;
};



#endif // DICCIONARIO_H