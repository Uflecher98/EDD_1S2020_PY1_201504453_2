#include "FichasJuego.h"

 Doble::Doble(){
     primero = NULL;
     ultimo = NULL;
   }


   void Doble::Insertar(int id, int valor, char letra){
       
       
     
       NodoD *nuevo = new NodoD();
       nuevo->id = letra+id;
       nuevo->valor = valor;
       nuevo->letra = letra;
       nuevo->ide += letra + std::to_string(id);
       
       if (primero == NULL){
             
           primero = nuevo;
           primero->siguiente = NULL;
           primero->anterior = NULL;
           ultimo = primero;
       }else {
           ultimo ->siguiente = nuevo;
           nuevo -> siguiente = NULL;
           nuevo->anterior = ultimo;
           ultimo = nuevo;
       } 
   }
   NodoD* Doble::Eliminar(char id){
       NodoD *actual = primero;
       NodoD *anterior  = NULL;
       bool enc = false;
       
       if(primero != NULL){
           while(actual != NULL && enc != true){

               if (actual->letra == id) {
                    if(primero==ultimo){
                        primero =NULL;
                        ultimo = NULL;
                    }
                   else if (actual == primero){
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
                   return actual;

                  
               }
              anterior = actual;
              actual = actual -> siguiente;
           }
        if (!enc){
            cout<<"No existe esa letra en tu mano\n";
            return NULL;
        }

       } else {
           cout<<"Lista vacía";
       }
   }

   void Doble::Modificar(int n, int id, int valor, char letra){
        NodoD *actual = new NodoD();
       actual = primero;
       bool enc = false;
       
       if(primero != NULL){
           while(actual != NULL && enc != true){

            if(actual->id == n){
                actual->id = id;
                actual->valor = valor;
                actual->letra = letra;
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

Doble::~Doble(){

}


   void Doble::Mostrar(){
       NodoD *aux = primero;
  
       if (primero!= NULL){
           cout<<"\n";
         while (aux!= NULL){
            cout<<"[ id:"<<aux->id<<", letra: "<<aux->letra<<", valor:"<<aux->valor<<"]\n";
            aux= aux->siguiente;
         }
       } else {
           cout<<"La lista está vacía";
       }
   }

    void Doble::Vaciar(){
       NodoD *aux = primero;
       if (primero!= NULL){
        while (aux!= NULL){
            Eliminar(aux->letra);
            cout<<"Vaciando lista"<<endl;
            aux= aux->siguiente;
         } 
       } else {
           cout<<"La lista está vacía";
       }
   }

   void Doble::Graficar(string usuario){
    NodoD *temp=primero;
    char grafo[5000]="digraph G {\n node[shape=box, style=filled, color=turquoise]; \n edge[color=black];\n\n{rank=min;";
    char num[500]="";
    char buffer[100];
if(temp!=NULL){
if (primero->siguiente==NULL){

    
                 strcat(grafo,"\"");
               
                  strcpy(buffer,temp->ide.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"[label = \"");
                  sprintf(num, "%c", temp->letra);
                  strcat(grafo,num);
                  strcat(grafo,"\"];");
                  strcat(grafo,"};\n");  
}else {
    


                  strcat(grafo,"\"");
                  strcpy(buffer,usuario.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\";");

//Nodos dentro del rank 

 do{
                  strcat(grafo,"\"");
               
                  strcpy(buffer,temp->ide.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"[label = \"");
                  sprintf(num, "%c", temp->letra);
                  strcat(grafo,num);
                  strcat(grafo,"\"];");
           
                 temp=temp->siguiente;

    } while (temp!=NULL);
 strcat(grafo,"};\n");




 temp = primero;

     do{
                   strcat(grafo,"\"");
                  strcpy(buffer,temp->ide.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"");

                  strcat(grafo,"->");

                  strcat(grafo,"\"");
                  strcpy(buffer,temp->siguiente->ide.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"");

                  strcat(grafo,"\n");
                 temp=temp->siguiente;
    } while (temp->siguiente!=NULL);

    temp=ultimo;

    while (temp->anterior!=NULL) {

            strcat(grafo,"\"");
                  strcpy(buffer,temp->ide.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"");

            strcat(grafo,"->");

            strcat(grafo,"\"");
                  strcpy(buffer,temp->anterior->ide.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\"");

            strcat(grafo,"\n");
            temp=temp->anterior;
        }
}
 


     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/FJugador.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/FJugador.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/FJugador.png");
    // system("nohup display /home/ulysses/Escritorio/Lista.png &");
    //system("eog Reportes/FJugador.png");
} else {
  cout<<"Fichas: Vacío"<<endl;
    strcat(grafo,"\"");
     strcpy(buffer,usuario.c_str());
    sprintf(num, "%s", buffer);
    strcat(grafo,num);
    strcat(grafo,"\";");
    strcat(grafo,"}}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/FJugador.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/FJugador.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/FJugador.png");
}
   }