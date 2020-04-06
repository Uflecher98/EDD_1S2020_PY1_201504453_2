#ifndef Usuarios_H
#define Usuarios_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "Scores.h"
#include "FichasJuego.h"

using namespace std;

class NodoUs{
    public:
    int id;
    string nombre;
    int acumulado;


    Lista Historial;
    Doble Fichas;

    NodoUs *izquierda;
    NodoUs *derecha;
    NodoUs *padre;

    friend class Arbol;
    };

class Arbol{

  public:
   
   Arbol();
   ~Arbol();

   void Insertar(NodoUs *& raiz, int id, string nombre, NodoUs * padre);
   NodoUs *CrearNodo(int, string, NodoUs *);
   NodoUs *BuscarNodo( NodoUs* arbol, string nombre);
   NodoUs *BuscarNodoID( NodoUs* arbol, int id);
   int setAcumulado(NodoUs *usuario, int acumulado);

   bool MinimoU();

   void InsertarScore(NodoUs *&usuario, int score);
   void InsertarFicha(NodoUs *&usuario, NodoD *ficha);

   void VaciarLJ(NodoUs *&usuario);
   void MostrarLista(NodoUs *&usuario);

   void GraficarFichas(NodoUs *usuario);
   void GraficarScores(NodoUs *usuario);
   
   void Mostrar(NodoUs * raiz);
   bool busqueda( NodoUs *, string);

   void preOrden(NodoUs *);
   void inOrden(NodoUs *);
   void postOrden(NodoUs *);
   void Recorrido(NodoUs *);
   void Recorrido_(NodoUs *);

//Graficas
  void GraPre();
  void GraIn();
  void GraPost();
  
   void GrafpreOrden(NodoUs *);
   void GrafinOrden(NodoUs *);
   void GrafpostOrden(NodoUs *);

   void Eliminar(NodoUs *, string);
   void EliminarNodo(NodoUs *);
   void reemplazar(NodoUs*, NodoUs*);
   NodoUs *mi(NodoUs*); 
   void DestruirNodo(NodoUs *);

   void GraficarArbol();


   NodoUs *raiz ;
};


#endif 