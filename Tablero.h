#ifndef Tablero_H
#define Tablero_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<cstdlib>

using namespace std;

class NodoMatriz{
   public:
    int x, y;
    char letra;
    int valor;
    int id;
    bool dob, tri, d, t;
    string ide;

    NodoMatriz *anterior;
    NodoMatriz *siguiente;
    NodoMatriz *arriba;
    NodoMatriz *abajo;

    NodoMatriz(int x, int y, char letra, int valor, int id, bool dob, bool tri, bool i, bool f, string ide);

};

class Matriz{
    public:

        Matriz();
        NodoMatriz * BuscarFila(int y);
        NodoMatriz * BuscarColumna(int x);
        NodoMatriz * BuscarNodo(int x, int y);
        
        void Insertar(int x, int y, char letra, int valor, int id, bool dob, bool tri, bool d, bool t, string ide);
        NodoMatriz *CrearColumna(int x);
        NodoMatriz *CrearFila(int y);
        NodoMatriz * OrdenadoCol(NodoMatriz *nuevo, NodoMatriz *cabezacol);        
        NodoMatriz * OrdenadoFila(NodoMatriz *nuevo, NodoMatriz *cabezafila); 

        void RecorrerMatriz(NodoMatriz *raiz);
        void VaciarMatriz(NodoMatriz *raiz);

        NodoMatriz * EliminarNodo(int x, int y);

        void EliminarCabFila(int y);
        void EliminarCabColumna(int x);

        void GraficarMatriz(NodoMatriz *raiz);
        void Graficar();

      

        NodoMatriz *raiz;
};


#endif