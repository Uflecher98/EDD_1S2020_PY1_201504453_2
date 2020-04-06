#include "Diccionario.h"

ListaDoble::ListaDoble(){
     primero = NULL;
     ultimo = NULL;
   }

   
  void  ListaDoble::InsertarRef(int  referencia, string c, int i){
       Nodo_LD *nuevo = new Nodo_LD();
       nuevo->palabra = c;
       nuevo->id = i;

      Nodo_LD *actual = new Nodo_LD();
       actual = primero;
       bool enc = false;

       Nodo_LD *n = new Nodo_LD();

            while(actual != NULL && enc != true){

            if(actual->id ==  referencia){ //Encontró el nodo 
                n = actual;
                enc= true;
            }
           
              actual = actual -> siguiente;
           }
     
       if (primero == NULL){ //Vacío
               
           primero = nuevo;
        
           primero->siguiente = primero;
           primero->anterior = primero;
           
        
       }else if(n==primero){ //Al frente 
           
           ultimo ->siguiente = nuevo;
           nuevo -> siguiente = ultimo;
           nuevo->anterior = ultimo;
           ultimo = nuevo;
       } else { //insertar después de 

           n->siguiente->anterior = nuevo;
           nuevo->siguiente = n->siguiente;
           n->siguiente = nuevo;
           nuevo->anterior = n;
       }
   }


void ListaDoble::Insertar( string c, int i){
       
       
     
       Nodo_LD *nuevo = new Nodo_LD();
       nuevo->palabra = c;
       nuevo->id = i;

       if (primero == NULL){
          
           primero = nuevo;
           ultimo = nuevo;
           primero->siguiente = primero;
           primero->anterior = ultimo;
       }else {
             
           ultimo->siguiente = nuevo;
           nuevo->anterior = ultimo;
           nuevo->siguiente = primero;
           ultimo = nuevo;
           primero->anterior = ultimo;      
       } 
   }

void ListaDoble::Eliminar(int id){
       Nodo_LD *actual = new Nodo_LD();
       actual = primero;
       Nodo_LD *anterior = new Nodo_LD();
       anterior = NULL;
       bool enc = false;
       
       if(primero != NULL){
           while(actual != NULL && enc != true){

               if (actual->id == id) {
               
                   if (actual == primero){
                       primero = primero->siguiente ;
                       primero->anterior = NULL;
                   } else if(actual == ultimo){
                       anterior->siguiente = NULL;
                       ultimo = anterior;
                   } else{
                       anterior->siguiente = actual ->siguiente;
                       actual->siguiente->anterior = anterior;
                   }

                   enc = true;
               }
              anterior = actual;
              actual = actual -> siguiente;
           }
        if (!enc){
            cout<<"Nodo no encontrado ";
        }

       } else {
           cout<<"Lista vacía";
       }
   }

   void ListaDoble::Modificar(int n, int id, string c){
        Nodo_LD *actual = new Nodo_LD();
       actual = primero;
       bool enc = false;
       
       if(primero != NULL){
           while(actual != NULL && enc != true){

            if(actual->id == n){
                actual->id = id;
                actual->palabra = c;
                enc= true;
            }
           
              actual = actual -> siguiente;
           }
        if (!enc){
            cout<<"Nodo no encontrado ";
        }

       } else {
           cout<<"Lista vacía";
       }
   }



   void ListaDoble::Mostrar(){
       Nodo_LD *aux = new Nodo_LD();
       aux = primero;
     
    if (primero != NULL){
        do {
        cout<<" ["<<aux->id<<", "<<aux->palabra<<"] <--->";
        aux = aux->siguiente;}
    
      while(aux != primero);
        
    } else {
     cout<<"La lista está vacía";
    }
   }

   bool ListaDoble::BuscarNodo(string palabra){
       Nodo_LD *actual = primero;
       if (primero!=ultimo){
           while(actual != primero){
               if(actual->palabra == palabra){
                   return true;
               }
               actual = actual->siguiente;
           }
           return false;
       } else{
           cout<<"Lista vacía"<<endl;
       }
   }



   void ListaDoble::Graficar(){
        Nodo_LD *temp=primero;
    char grafo[5000]="";
    char num[500]="";
    char buffer[100];
    strcat(grafo,"digraph G {\n node[shape=box, style=filled, color=turquoise]; \n edge[color=black];\n\n{rank=min;");

//Nodos dentro del rank 

 do{
                  strcat(grafo,"\"");
                  strcpy(buffer,temp->palabra.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\";");
           
                 temp=temp->siguiente;

    } while (temp!=primero);
 strcat(grafo,"};\n");

//Enlaces 

temp = primero;

     do{
                  strcat(grafo,"\"");

                  strcpy(buffer,temp->palabra.c_str());

                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"");

                  strcat(grafo,"->");

                  strcat(grafo,"\"");
                  strcpy(buffer,temp->siguiente->palabra.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"");

                  strcat(grafo,"\n");
                 temp=temp->siguiente;
    } while (temp!=ultimo);

    temp=ultimo;

    while (temp!=primero) {

            strcat(grafo,"\"");
            strcpy(buffer,temp->palabra.c_str());
            sprintf(num, "%s", buffer);
            strcat(grafo,num);
            strcat(grafo,"\"");

            strcat(grafo,"->");

            strcat(grafo,"\"");
            strcpy(buffer,temp->anterior->palabra.c_str());
            sprintf(num, "%s", buffer);
            strcat(grafo,num);
            strcat(grafo,"\"");

            strcat(grafo,"\n");
            temp=temp->anterior;
        }

    temp = primero;

            strcat(grafo,"\"");
            strcpy(buffer,temp->palabra.c_str());
            sprintf(num, "%s", buffer);
            strcat(grafo,num);
            strcat(grafo,"\"");

            strcat(grafo,"->");

            strcat(grafo,"\"");
            strcpy(buffer,temp->anterior->palabra.c_str());
            sprintf(num, "%s", buffer);
            strcat(grafo,num);
            strcat(grafo,"\"");

            strcat(grafo,"\n");

    temp = ultimo;

       strcat(grafo,"\"");
       strcpy(buffer,temp->palabra.c_str());
            sprintf(num, "%s", buffer);
            strcat(grafo,num);
            strcat(grafo,"\"");

            strcat(grafo,"->");

            strcat(grafo,"\"");
            strcpy(buffer,temp->siguiente->palabra.c_str());
            sprintf(num, "%s", buffer);
            strcat(grafo,num);
            strcat(grafo,"\"");

            strcat(grafo,"\n");

    


     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/Diccionario.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -T pdf /home/ulysses/Escritorio/Proyecto/Reportes/Diccionario.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/Diccionario.png");
    // system("eog Reportes/Diccionario.png");
   //  system("nohup display /home/ulysses/Escritorio/Diccionario.png &");
   }

 
    
   ListaDoble::~ListaDoble(){
     
   }