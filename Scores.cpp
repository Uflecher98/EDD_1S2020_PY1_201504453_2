#include "Scores.h"

Lista::Lista(){
    lista = NULL;
};

Lista::~Lista(){

};
//void Lista::Insertar(Nodo *&lista, string nombre, int score){
void Lista::Insertar(string nombre, int score){
    Nodo *nuevo = new Nodo();
    nuevo->jugador = nombre;
    nuevo->punteo = score;

    Nodo *aux1 = lista;
    Nodo *aux2;

    while((aux1 != NULL) && (aux1->punteo > score)){
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }

    if(lista == aux1){
        lista = nuevo;
        nuevo->siguiente = aux1;
    } else {
        aux2->siguiente = nuevo;
    }

    nuevo->siguiente = aux1;

}

void Lista::Mostrar(Nodo *lista){
    Nodo *actual = new Nodo();
    actual = lista;

    while (actual != NULL){
       cout<<actual->jugador<<": "<<actual->punteo<<"   --> ";
       actual = actual->siguiente; 
    }
    
}

void Lista::Buscar(Nodo *lista, int n){
    bool x = false;

    Nodo *actual = new Nodo();
    actual = lista;

    while((actual != NULL) && (actual->punteo <= n)){
        if (actual -> punteo == n){
            x= true;
            cout<<"El nombre es: "<<actual->jugador;
        }
        actual = actual ->siguiente;
    }

    if (x==true){
        cout<<"Elemento "<<n<<" Se encontró";

    } else {
        cout<<"Elemento no Se encontró";
    }
}

void Lista::Eliminar(Nodo *&lista, int n){
    if (lista != NULL ){
        Nodo *aux1;
        Nodo *ante = NULL;
        aux1 = lista;

        while ((aux1 !=NULL)&&(aux1->punteo != n)){
            ante = aux1;
            aux1 = aux1->siguiente;
        }

        if (aux1 == NULL){
            cout<<"El elemento no existe";

        }else if (ante == NULL){
            lista = lista -> siguiente;
            delete aux1;

        } else {
            ante ->siguiente= aux1->siguiente;
            delete aux1;
        }
    }
}

  void Lista::GraficarGlobal(){
    Nodo *temp=lista;
    char grafo[5000]="";
    char num[500]="";
    char buffer[100];
      strcat(grafo,"digraph G {\n node[shape=box, style=filled, color=turquoise]; \n edge[color=black];\n\n{rank=min;");

//Nodos dentro del rank 

 do{
                  strcat(grafo,"\"");
                  strcpy(buffer,temp->jugador.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);

                  strcat(grafo,":");
                  
                  sprintf(num, "%d", temp->punteo);
                  strcat(grafo,num);

                  strcat(grafo,"\";");
           
                 temp=temp->siguiente;

    } while (temp!=NULL);
 strcat(grafo,"};\n");



 temp = lista;

     do{
                  strcat(grafo,"\"");
                  strcpy(buffer,temp->jugador.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);

                  strcat(grafo,":");
                  
                  sprintf(num, "%d", temp->punteo);
                  strcat(grafo,num);

                  strcat(grafo,"\"->");

                strcat(grafo,"\"");
                  strcpy(buffer,temp->siguiente->jugador.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);

                  strcat(grafo,":");
                  
                  sprintf(num, "%d", temp->siguiente->punteo);
                  strcat(grafo,num);


                  strcat(grafo,"\"");

                  strcat(grafo,"\n");
                 temp=temp->siguiente;
    } while (temp->siguiente!=NULL);

   
    

 
     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/ScoreBoard.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/ScoreBoard.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/ScoreBoard.png");
     //system("eog Reportes/ScoreBoard.png");
    // system("nohup display /home/ulysses/Escritorio/Lista.png &");
}


  void Lista::GraficarIndividual(){
    Nodo *temp=lista;
    char grafo[5000]="";
    char num[500]="";
    char buffer[100];
      strcat(grafo,"digraph G {\n node[shape=box, style=filled, color=turquoise]; \n edge[color=black];\n\n{rank=min;");

//Nodos dentro del rank 

                  strcat(grafo,"\"");
                  strcpy(buffer,temp->jugador.c_str());
                  sprintf(num, "%s", buffer);
                  strcat(grafo,num);
                  strcat(grafo,"\";");

 do{
                  strcat(grafo,"\"");     
                  sprintf(num, "%d", temp->punteo);
                  strcat(grafo,num);
                  strcat(grafo,"\";");
           
                 temp=temp->siguiente;

    } while (temp!=NULL);
 strcat(grafo,"};\n");



 temp = lista;

     while (temp->siguiente!=NULL){

                  strcat(grafo,"\"");
                  sprintf(num, "%d", temp->punteo);
                  strcat(grafo,num);


            if(temp->siguiente == NULL){
                  strcat(grafo,"\";");
            } else {
                strcat(grafo,"\"->\"");  
                  sprintf(num, "%d", temp->siguiente->punteo);
                  strcat(grafo,num);
                  strcat(grafo,"\"\n");
            }
                  
                 temp=temp->siguiente;
    } 

   
     strcat(grafo,"}");
     FILE* fichero;
     fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/HistorialJ.dot","wt");
     fputs(grafo,fichero);
     fclose(fichero);
     system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/HistorialJ.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/HistorialJ.png");
    //system("eog Reportes/HistorioalJ.png");
    //system("nohup display /home/ulysses/Escritorio/Lista.png &");
}