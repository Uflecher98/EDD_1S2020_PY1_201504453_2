
#include "Fichas.h"

Cola::Cola(){
    frente = NULL;
    fin = NULL;
};

Cola::~Cola(){

};
//void Cola::Insertar(NodoCola *& frente, NodoCola *& fin, int id, int valor, char letra)

void Cola::Insertar(int id, int valor, char letra){
    NodoD * nuevo = new NodoD();
    nuevo->id = id;
    nuevo->valor = valor;
    nuevo->letra = letra;
    nuevo->siguiente = NULL;
    nuevo->ide += letra + std::to_string(id);

    if (Cola_Vacia(frente)){
       frente = nuevo;
    } else {
        fin->siguiente = nuevo;
    }

    fin = nuevo;
};

bool Cola::Cola_Vacia(NodoD *frente){
   
    return (frente==NULL)? true : false;
};

int Cola::contar(){
    int cont=0;
    NodoD * temp = frente;
  if(frente!=NULL){
      while (temp!=NULL)
      {
          cont++;
          temp = temp->siguiente;
      }
      return cont;
      
  } else {
      cout<<"La cola está vacía";
  }
}

void Cola::Vaciar(){
    int cont=0;
    NodoD * temp = frente;
  if(frente!=NULL){
      while (temp!=NULL)
      {
          Eliminar();
          temp = temp->siguiente;
      }     
  } else {
      cout<<"La cola está vacía";
  }
};

NodoD* Cola::Eliminar(){
    
    NodoD *aux = frente;

    if (frente == fin){
        frente = NULL;
        fin = NULL;
    } else {
        frente = frente ->siguiente;       
    }
    return aux;
}

   void Cola::Graficar(){
       if(frente!=NULL){

    NodoD *temp=frente;
    char grafo[5000]="";
    char num[500]="";
    char buffer[10];
      strcat(grafo,"graph G {\n node[shape=box, style=filled, color=turquoise]; \n edge[color=black];\n");


     do{
                  strcat(grafo,"\"");
                  strcpy(buffer,temp->ide.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"[label = \"");
                  sprintf(num, "%c", temp->letra);
                  strcat(grafo,num);
                  strcat(grafo,"\"];\n");

                
                 temp=temp->siguiente;
    } while (temp!=NULL);


     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/Cola.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/Cola.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/Cola.png");
     //system("eog Reportes/Cola.png");
    // system("nohup display /home/ulysses/Escritorio/Lista.png &");
       } else {
               char grafo[5000]="";
    char num[500]="";
    char buffer[10];
      strcat(grafo,"graph G {\n node[shape=box, style=filled, color=turquoise]; \n edge[color=black];\n");
       strcat(grafo,"\"Cola Vacía\";}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/Cola.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/Cola.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/Cola.png");
     //system("eog Reportes/Cola.png");
       }
}