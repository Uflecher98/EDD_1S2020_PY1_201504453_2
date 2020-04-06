
#include "Usuarios.h"

Arbol::Arbol(){
  raiz = NULL;
}

int Arbol::setAcumulado(NodoUs* usuario, int acumulado){
    usuario->acumulado += acumulado;
}

NodoUs *Arbol::CrearNodo(int id, string n, NodoUs * padre){
  NodoUs *nuevo = new NodoUs();
  nuevo->id = id;
  nuevo->nombre = n;
  nuevo->derecha = NULL;
  nuevo->izquierda = NULL;
  nuevo->padre = padre;

  return nuevo;
};

bool Arbol::MinimoU(){
    if (raiz!=NULL && raiz->derecha!=NULL){
        return true;
    }
    else if (raiz!=NULL && raiz->izquierda!=NULL){
        return true ;
    }
    else {
        return false;
    }
}


void Arbol::Insertar(NodoUs *&raiz, int id, string n, NodoUs * padre){

    if (raiz == NULL){
        NodoUs *nuevo = CrearNodo(id, n, padre);
        raiz = nuevo;
    } else {
        string nombre = raiz->nombre;
        if (n == nombre){
            return;
        } else {
        if (n.compare(nombre)<0){
            Insertar(raiz->izquierda, id,  n, raiz);
        } else {
            Insertar(raiz->derecha, id, n, raiz);
        }
        }
    }
};


void Arbol::Mostrar(NodoUs *arbol){
     
    if (arbol == NULL){
           return;
     } else {
          Mostrar(arbol->izquierda);
          cout <<arbol->nombre<<endl;
          Mostrar(arbol->derecha);
    }
   
}



Arbol::~Arbol(){

};

bool Arbol::busqueda(NodoUs *arbol, string nombre){
    if (arbol == NULL){
        return false;
    } else if (arbol->nombre == nombre){
        return true;
    } else if (nombre.compare(arbol->nombre)<1){
        return busqueda(arbol->izquierda, nombre);
    } else {
        return busqueda(arbol->derecha, nombre);
    }
};

NodoUs * Arbol::BuscarNodo(NodoUs *arbol, string nombre){
      if (arbol == NULL){
        return arbol;
    } else if (arbol->nombre == nombre){
        cout<<"Se encontró a: "<<arbol->nombre<<endl;
        return arbol;
    } else if (nombre.compare(arbol->nombre)<1){
        return BuscarNodo(arbol->izquierda, nombre);
    } else {
        return BuscarNodo(arbol->derecha, nombre);
    }
}

NodoUs * Arbol::BuscarNodoID(NodoUs *arbol, int id){
      if (arbol == NULL){
        return arbol;
    } else if (arbol->id == id){
        cout<<"Se encontró por ID a: "<<arbol->nombre<<endl;
        return arbol;
    } else if (id < arbol->id){
        return BuscarNodoID(arbol->izquierda, id);
    } else {
        return BuscarNodoID(arbol->derecha, id);
    }
}


//Referencia? 

void Arbol::InsertarScore(NodoUs *&usuario, int score){
        usuario->Historial.Insertar(usuario->nombre, score);
}   

void Arbol::VaciarLJ(NodoUs *&usuario){
    usuario->Fichas.Vaciar();
}

void Arbol::MostrarLista(NodoUs *&Usuario){
    Usuario->Fichas.Mostrar();
}
void Arbol::InsertarFicha(NodoUs *&usuario, NodoD *ficha){
    int id = ficha->id;
    int valor = ficha->valor;
    char letra = ficha->letra;
    usuario->Fichas.Insertar(id, valor, letra);  
}

void Arbol::GraficarFichas(NodoUs *usuario){
    usuario->Fichas.Graficar(usuario->nombre);
}

void Arbol::GraficarScores(NodoUs *usuario){
    usuario->Historial.GraficarIndividual();
}

 void Arbol::preOrden(NodoUs *arbol){
       
       if (arbol == NULL){
           return;
       } else {
           cout <<arbol->nombre<<" - ";
           preOrden(arbol->izquierda);
           preOrden(arbol->derecha);
       }
   }


   void Arbol::inOrden(NodoUs *arbol){
       
           if (arbol == NULL){
           return;
       } else {
           inOrden(arbol->izquierda);
           cout <<arbol->nombre<<" - ";
           inOrden(arbol->derecha);
       }
   };

   void Arbol::postOrden(NodoUs *arbol){
     if (arbol == NULL){
           return;
       } else {
           postOrden(arbol->izquierda);
           postOrden(arbol->derecha);
           cout <<arbol->nombre<<" - ";
           
       }
   };
   
   void Arbol::Eliminar(NodoUs * arbolNodo, string n){
       if (arbolNodo== NULL){
           return;
       } else if (n.compare(arbolNodo->nombre)<0) {
           Eliminar(arbolNodo->izquierda,n);
       } else if (n.compare(arbolNodo->nombre)>0){
           Eliminar(arbolNodo->derecha, n);
       } else {
           EliminarNodo(arbolNodo);
       }
   };

NodoUs *Arbol::mi(NodoUs *arbol){
    if(arbol == NULL){
        return NULL;
    } 
    if(arbol->izquierda){
        return mi(arbol->izquierda);
    } else {
        return arbol;
    } 
}

void Arbol::DestruirNodo(NodoUs * nodo){
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    delete nodo;
}

   void Arbol::EliminarNodo(NodoUs *NodoEli){
       if(NodoEli->izquierda && NodoEli->derecha){
           NodoUs *menor = mi(NodoEli->derecha);
           NodoEli ->nombre = menor->nombre;
           EliminarNodo(menor);
       } else if (NodoEli->izquierda){
            reemplazar(NodoEli, NodoEli->izquierda);
            DestruirNodo(NodoEli);
       } else if(NodoEli->derecha){
           reemplazar(NodoEli, NodoEli->derecha);
           DestruirNodo(NodoEli);
       } else{
           reemplazar(NodoEli, NULL);
           DestruirNodo(NodoEli);
       }
       
   }

   void Arbol::reemplazar(NodoUs *arbol, NodoUs*nuevo){
       if(arbol->padre){
           if(arbol->nombre == arbol->padre->izquierda->nombre){
               arbol->padre->izquierda = nuevo;
           } else if(arbol->nombre == arbol->padre->derecha->nombre){
               arbol->padre->derecha = nuevo;
           }
       }
       if(nuevo){
           nuevo->padre = arbol->padre;
       }
   }

char grafo[5000]="";
char num[500]="";
char buffer[100];


   void Arbol::Recorrido_(NodoUs *arbol){
       
       if (arbol == NULL){
           return;
       } else {
           strcpy(buffer,arbol->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo,"[label = \"<i>|"); 
           strcpy(buffer,arbol->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo,"|<d>\"];\n"); 
           cout <<arbol->nombre<<" - ";
           Recorrido_(arbol->izquierda);
           Recorrido_(arbol->derecha);
       }
   }

void Arbol::Recorrido(NodoUs *arbol){
    if (arbol == NULL){
           return;
       } else {
          
          if(arbol->izquierda!= NULL){
              strcpy(buffer,arbol->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo,":i -> "); 
           strcpy(buffer,arbol->izquierda->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo,";\n");
          }

          if(arbol->derecha!= NULL){
               strcpy(buffer,arbol->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo,":d -> "); 
           strcpy(buffer,arbol->derecha->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo,";\n");
          }
           
           Recorrido(arbol->izquierda);
           Recorrido(arbol->derecha);
           
       }
}
   void Arbol::GraficarArbol(){
    memset(grafo, 0, 5000);
    memset(num, 0, 500);
    NodoUs *arbol=raiz;
   
      strcat(grafo,"digraph G {\n rankdir=TB;\n node [shape = record, style=filled, fillcolor=seashell2];\n");
      
      Recorrido_(arbol);
      strcat(grafo,"\n"); 
 
     arbol = raiz;
     Recorrido(arbol);
     
     
     
    
     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/ArbolU.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/ArbolU.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/ArbolU.png");
     //system("eog Reportes/ArbolU.png");
    // system("nohup display /home/ulysses/Escritorio/Lista.png &");
   }

// =========================================================================================



    void Arbol::GrafpreOrden(NodoUs *arbol){

       if (arbol == NULL){
           return;
       } else {
           strcpy(buffer,arbol->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo," -> ");
           GrafpreOrden(arbol->izquierda);
           GrafpreOrden(arbol->derecha);
       }
   }

   void Arbol::GraPre(){
       memset(grafo, 0, 5000);
     memset(num, 0, 500);
    NodoUs *arbol=raiz;

      strcat(grafo,"digraph G {\n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n");
   
      GrafpreOrden(arbol);
     strcat(grafo,"null;\n"); 

     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/PreOrden.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/PreOrden.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/PreOrden.png");
     system("eog Reportes/PreOrden.png");
   }



//============================================================================================


   void Arbol::GrafinOrden(NodoUs *arbol){
       
           if (arbol == NULL){
           return;
       } else {
           GrafinOrden(arbol->izquierda);
           strcpy(buffer,arbol->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo," -> ");
           GrafinOrden(arbol->derecha);
       }
   }

    void Arbol::GraIn(){
         memset(grafo, 0, 5000);
     memset(num, 0, 500);
    NodoUs *arbol=raiz;

      strcat(grafo,"digraph G {\n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n");
   
      GrafinOrden(arbol);
     strcat(grafo,"null;\n"); 

     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/InOrden.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/InOrden.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/InOrden.png");
     system("eog Reportes/InOrden.png");
   }
 
 

//===========================================================================================
   


   void Arbol::GrafpostOrden(NodoUs *arbol){
     if (arbol == NULL){
           return;
       } else {
           GrafpostOrden(arbol->izquierda);
           GrafpostOrden(arbol->derecha);
           strcpy(buffer,arbol->nombre.c_str());
           sprintf(num, "%s", buffer);
           strcat(grafo,num);
           strcat(grafo," -> ");
           
       }
   }

   void Arbol::GraPost(){
        memset(grafo, 0, 5000);
     memset(num, 0, 500);
        NodoUs *arbol=raiz;

      strcat(grafo,"digraph G {\n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n");
   
      GrafpostOrden(arbol);
     strcat(grafo,"null;\n"); 

     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/PostOrden.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/PostOrden.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/PostOrden.png");
     system("eog Reportes/PostOrden.png");
   }