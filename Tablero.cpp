#include "Tablero.h"

Matriz::Matriz(){
    raiz = new NodoMatriz(-1, -1, 'R', 0, 0, 0, 0, 0, 0, "root");  
   
}




NodoMatriz::NodoMatriz(int x, int y, char letra, int valor, int id, bool dob, bool tri, bool i, bool f, string ide){
    this->x= x;
    this->y= y;
    this->letra = letra;
    this->valor= valor;
    this->id =id;
    this->dob = dob;
    this->tri = tri;
    this->d = i;
    this->t = f;
    this->ide = ide;

    
    this->anterior = NULL;
    this->siguiente = NULL;
    this->arriba = NULL;
    this->abajo = NULL;
}







NodoMatriz *Matriz::BuscarFila(int y){
    NodoMatriz *temp =  raiz;
    while (temp!=NULL)
    {
        if(temp->y == y){
            return temp;
        }
        temp = temp->abajo;
    }
    return NULL;
}

NodoMatriz *Matriz::BuscarColumna(int x){
    NodoMatriz *temp =  raiz;
    while (temp!=NULL)
    {
        if(temp->x == x){
            return temp;
        }
        temp = temp->siguiente;
    }
    return NULL;
}

NodoMatriz *Matriz::BuscarNodo(int x, int y){
           NodoMatriz* temporal=raiz->abajo;
    //cout<<"Nodo a buscar: ["<<x<<", "<<y<<"]"<<endl;
    if(temporal!=NULL){
        while (temporal!=NULL)
        {   
            NodoMatriz* auxiliar = temporal;


            if(auxiliar!=NULL){
                 while (auxiliar!=NULL) {
                    //cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";

                        if (auxiliar->x == x && auxiliar->y==y){      
                            cout<<"Casilla Encontrada"<<endl;       
                            return auxiliar;
                        }
                  auxiliar = auxiliar->siguiente;
                }
            }  


            cout<<"\n";
            temporal = temporal->abajo;
        }
    }
    cout<<"Nodo no encontrado :(";
    return NULL;
}

NodoMatriz *Matriz::OrdenadoCol(NodoMatriz *nuevo, NodoMatriz *cabezacol){
    NodoMatriz *temp = cabezacol;
    bool bandera = false;
    while (true)
    {
        if (temp->x == nuevo->x){
            temp->y = nuevo->y;
            temp->letra = nuevo->letra;
            temp->valor = nuevo->valor;
            return temp;
        }
        else if(temp->x > nuevo->x){
            bandera = true; //insertar antes de temp
            break;
        }
        if (temp->siguiente != NULL){ 
            temp = temp->siguiente;
        } else { //insertar despues de temp
            break;
        }
    }

    if (bandera){
        nuevo->siguiente = temp;
        temp->anterior->siguiente = nuevo;
        nuevo->anterior = temp->anterior;
        temp->anterior = nuevo;
    } else {
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
    }
    return nuevo;
}

NodoMatriz *Matriz::OrdenadoFila(NodoMatriz *nuevo, NodoMatriz *cabezafila){
    NodoMatriz *temp = cabezafila;
    bool bandera = false;
    while (true)
    {
        if (temp->y == nuevo->y){
            temp->x = nuevo->x;
            temp->letra = nuevo->letra;
            temp->valor = nuevo->valor;
            return temp;
        }
        else if(temp->y > nuevo->y){
            bandera = true; //insertar antes de temp
            break;
        }
        if (temp->abajo != NULL){ 
            temp = temp->abajo;
        } else { //insertar despues de temp
            break;
        }
    }

    if (bandera){
        nuevo->abajo = temp;
        temp->arriba->abajo = nuevo;
        nuevo->arriba = temp->arriba;
        temp->arriba = nuevo;
    } else {
        temp->abajo = nuevo;
        nuevo->arriba = temp;
    }
    return nuevo;
}

void Matriz::Insertar(int x, int y, char letra, int valor, int id, bool dob, bool tri, bool d, bool t, string ide){
    NodoMatriz *nuevo = new NodoMatriz(x,y,letra,valor, id, dob, tri, d, t, ide);
    NodoMatriz *columna =  BuscarColumna(x);
    NodoMatriz *fila = BuscarFila(y);

    //CASO 1: NO COLUMNA, NO FILA 
     if ((columna == NULL) && (fila == NULL)){
       
         //Se crea la columna 
         columna = CrearColumna(x);
         //Se crea la fila 
         fila = CrearFila(y);
         //Insertar en columna
         nuevo = OrdenadoCol(nuevo, fila);
         //Insertar en fila
         nuevo = OrdenadoFila(nuevo, columna);
        // cout<<"Se insertó dato sin fila ni columna creada\n";
         return;
     }
    //CASO 2: NO COLUMNA, SI FILA
     else if ((columna == NULL) && (fila != NULL)){
       
         //Se crea la columna 
         columna = CrearColumna(x);
         //Insertar en columna
         nuevo = OrdenadoCol(nuevo, fila);
         //Insertar en fila
         nuevo = OrdenadoFila(nuevo, columna);
        // cout<<"Se insertó dato sin  columna creada\n";
         return;
     }
    //CASO 3: SI COLUMNA, NO FILA 
      else if ((columna != NULL) && (fila == NULL)){

         //Se crea la fila 
          fila = CrearFila(y);
         //Insertar en columna
         nuevo = OrdenadoCol(nuevo, fila);
         //Insertar en fila
         nuevo = OrdenadoFila(nuevo, columna);
         //cout<<"Se insertó dato sin fila creada\n";
         return;
      }
    //CASO 4: SI COLUMNA, SI FILA
      else {
    
         //Insertar en columna
         nuevo = OrdenadoCol(nuevo, fila);
         //Insertar en fila
         nuevo = OrdenadoFila(nuevo, columna);
         //cout<<"Se insertó dato con columna y fila creada\n";
      }

}
int cc, cf = 0; 

NodoMatriz *Matriz::CrearColumna(int x){
    cc++;
    NodoMatriz *cabezacolumna =  raiz;
    NodoMatriz *columna = OrdenadoCol(new NodoMatriz(x,-1,'C',-1, cc,false,false,false,false, "col"),cabezacolumna);
    return columna;
}

NodoMatriz *Matriz::CrearFila(int y){
    cf++;
    NodoMatriz *cabezafila = raiz;
    NodoMatriz *fila = OrdenadoFila(new NodoMatriz(-1, y, 'F', -1, cf,false,false,false,false, "fil"),cabezafila);
    return fila;
}


void Matriz::RecorrerMatriz(NodoMatriz *_raiz){
    cout<<"Raiz: "<<raiz->x<<", "<<raiz->y<<", "<<raiz->letra<<endl;
    NodoMatriz* temporal=_raiz;

    if(temporal!=NULL){
        while (temporal!=NULL)
        {   
            NodoMatriz* auxiliar = temporal;
            if(auxiliar!=NULL){
                 while (auxiliar!=NULL) {
                    cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                    auxiliar = auxiliar->siguiente;
                }
            }
           
            cout<<"\n";
            temporal = temporal->abajo;
        }
           
    }
}

void Matriz::VaciarMatriz(NodoMatriz *_raiz){
    cout<<"Raiz: "<<raiz->x<<", "<<raiz->y<<", "<<raiz->letra<<endl;
    NodoMatriz* temporal=_raiz->abajo;

    if(temporal!=NULL){
        while (temporal!=NULL)
        {   
            NodoMatriz* auxiliar = temporal->siguiente;
            if(auxiliar!=NULL){
                 while (auxiliar!=NULL) {
                    cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                    EliminarNodo(auxiliar->x, auxiliar->y);
                    auxiliar = auxiliar->siguiente;
                }
            }
           
            cout<<"\n";
            temporal = temporal->abajo;
        }
           
    }
}

void Matriz::EliminarCabFila(int y){
    NodoMatriz * eli = raiz->abajo;
    if(eli!=NULL){
        while(eli!=NULL){
            if (eli->y == y){

                //if (eli->arriba == raiz){
                    if(eli->abajo!=NULL){
                        eli->arriba->abajo = eli->abajo;
                        eli->abajo->arriba = eli->arriba;
                    } else {
                        eli->arriba->abajo = NULL;
                        eli->arriba = NULL;
                    }
                //}

            }
            eli=eli->abajo;
        }
    } else {
        cout<<"Error";
    }
}

void Matriz::EliminarCabColumna(int x){
        NodoMatriz * eli = raiz->siguiente;
    if(eli!=NULL){
        while(eli!=NULL){
            if (eli->x == x){

               // if (eli->anterior == raiz){
                    if(eli->siguiente!=NULL){
                        eli->anterior->siguiente = eli->siguiente;
                        eli->siguiente->anterior = eli->anterior;
                    } else {
                        eli->anterior->siguiente = NULL;
                        eli->anterior = NULL;
                    }
               // } 

            }
            eli=eli->siguiente;
        }
    } else {
        cout<<"Error";
    }
}



NodoMatriz * Matriz::EliminarNodo(int x, int y){

 NodoMatriz * nodo = BuscarNodo(x, y);

       if(nodo!=NULL){

          // cout<<"Nodo listo:"<<endl;
          // cout<<"Nodo x: "<<nodo->x<<", y: "<<nodo->y<<endl;
        
        //Verificar enlaces en x 

            if(nodo->siguiente== NULL && nodo->anterior->x ==-1){ //Si esta solo 
                nodo->siguiente = NULL;
                nodo->anterior = NULL;
               
                EliminarCabFila(y);
            } else {
                //inicio
                if (nodo->siguiente==NULL){
                    nodo->anterior->siguiente = NULL;
                    nodo->anterior = NULL;

                } else{
                    nodo->anterior->siguiente = nodo->siguiente;
                    nodo->siguiente->anterior = nodo->anterior;

                } 
            }


           //Verificar enlaces en y 
            
            if(nodo->abajo== NULL && nodo->arriba->y==-1){
                nodo->abajo = NULL;
                nodo->arriba = NULL;
               
                EliminarCabColumna(x);
            } else {
                    if (nodo->abajo==NULL){
                    nodo->arriba->abajo = NULL;
                    nodo->arriba = NULL;

                } else{
                    nodo->arriba->abajo = nodo->abajo;
                    nodo->abajo->arriba = nodo->arriba;

                } 
            }
            
            return nodo;
       } else {
           return NULL;
       }

  
}





void Matriz::Graficar(){

    char grafo[300000]="digraph G{\n node[shape=box, style=filled, color=lightskyblue]; \n edge[color=black];\nrankdir=UD;\n";
    char num[5000]="";
    
//========================================RANK SAME FILA PRIMERA=========================================== 
   NodoMatriz* temp=raiz;
 if (temp->abajo!=NULL && temp->siguiente!=NULL){

    if(temp!=NULL){
       
            strcat(grafo,"{rank=same; ");

            NodoMatriz* auxiliar = temp;

            if(auxiliar!=NULL){
                 while (auxiliar!=NULL) {
                   // cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                     strcat(grafo,"\"[");
                     sprintf(num, "%c",auxiliar->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",auxiliar->x);
                     strcat(grafo,num);
                     strcat(grafo,"]\";");
                    auxiliar = auxiliar->siguiente;
                }
            }
            strcat(grafo,"}\n");

    }

//========================================RANK SAME RESTO =========================================== 
   temp=raiz->abajo;

    if(temp!=NULL){
        while (temp!=NULL)
        {   
            strcat(grafo,"{rank=same; ");

            NodoMatriz* auxiliar = temp;

            if(auxiliar!=NULL){
                   // cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                     strcat(grafo,"\"[");
                     sprintf(num, "%c",auxiliar->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",auxiliar->y);
                     strcat(grafo,num);
                     strcat(grafo,"]\";");
                    
            }
 
//------------------------------------NODOS DE LA MATRIZ--------------------------------------

            NodoMatriz* auxiliar2 = auxiliar->siguiente;

            if(auxiliar2!=NULL){
                 while (auxiliar2!=NULL) {
                  

                  if (auxiliar2->dob== true){
                     strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar2->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar2->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"[label = \" ");
                     //sprintf(num, "%c",auxiliar2->letra);
                     //strcat(grafo,num);
                     strcat(grafo,"\" color =\"yellow\" ];");
                  } else if (auxiliar2->tri == true){
                     strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar2->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar2->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"[label = \" ");
                     //sprintf(num, "%c",auxiliar2->letra);
                     //strcat(grafo,num);
                     strcat(grafo,"\" color =\"red\"];");
                  } else {
                     strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar2->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar2->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"[label = \" ");
                     sprintf(num, "%c",auxiliar2->letra);
                     strcat(grafo,num);
                     strcat(grafo,"\"];");
                  }   
        
                    
                   

                    auxiliar2 = auxiliar2->siguiente;
                }
            }
            strcat(grafo,"}\n");
            //cout<<"\n";
            temp = temp->abajo;
        }     
    }


    //===========================================================================================
    //Links cabeceras de columna
    temp=raiz;

    if(temp!=NULL){
    

            if(temp!=NULL){
                 do {
       
                     strcat(grafo,"\"[");
                     sprintf(num, "%c",temp->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",temp->x);
                     strcat(grafo,num);
                     strcat(grafo,"]\"");

                     strcat(grafo,"->");

                     strcat(grafo,"\"[");
                     sprintf(num, "%c",temp->siguiente->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",temp->siguiente->x);
                     strcat(grafo,num);
                     strcat(grafo,"]\"[dir=both];\n");

                    temp = temp->siguiente;
                } while (temp->siguiente!=NULL);
            }
           
          
    }
//===========================================================================================
 //Links horizontales 

 temp=raiz->abajo;

    if(temp!=NULL){
        while (temp!=NULL)
        {   
           

            NodoMatriz* auxiliar = temp;

            if(auxiliar!=NULL){
                   // cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                     strcat(grafo,"\"[");
                     sprintf(num, "%c",auxiliar->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",auxiliar->y);
                     strcat(grafo,num);
                     strcat(grafo,"]\"");

                     strcat(grafo,"->");

                      strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar->siguiente->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar->siguiente->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"[dir=both constraint=false];\n");
                    
            }
 
//------------------------------------NODOS DE LA MATRIZ--------------------------------------

            NodoMatriz* auxiliar2 = auxiliar->siguiente;

            if(auxiliar2->siguiente!=NULL){
                 do {
                   // cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                     strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar2->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar2->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"");

                     strcat(grafo,"->");

                      strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar2->siguiente->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar2->siguiente->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"[dir=both constraint=false];\n");

                    auxiliar2 = auxiliar2->siguiente;
                }while (auxiliar2->siguiente!=NULL);
            }
            strcat(grafo,"\n");
            //cout<<"\n";
            temp = temp->abajo;
        }     
    }


//===========================================================================================
   //Links cabeceras de fila
    temp=raiz;

    if(temp!=NULL){
    

            if(temp!=NULL){
                 do {
                   // cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                     strcat(grafo,"\"[");
                     sprintf(num, "%c",temp->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",temp->y);
                     strcat(grafo,num);
                     strcat(grafo,"]\"");

                     strcat(grafo,"->");

                     strcat(grafo,"\"[");
                     sprintf(num, "%c",temp->abajo->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",temp->abajo->y);
                     strcat(grafo,num);
                     strcat(grafo,"]\"[dir=both rankdir=UD];\n");

                    temp = temp->abajo;
                } while (temp->abajo!=NULL);
            }
           
          
    }
//===========================================================================================
//Links verticales
    temp=raiz->siguiente;

   if(temp!=NULL){
        while (temp!=NULL)
        {   
           

            NodoMatriz* auxiliar = temp;

            if(auxiliar!=NULL){
                   // cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                     strcat(grafo,"\"[");
                     sprintf(num, "%c",auxiliar->letra);
                     strcat(grafo,num);
                     sprintf(num, "%d",auxiliar->x);
                     strcat(grafo,num);
                     strcat(grafo,"]\"");

                     strcat(grafo,"->");

                      strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar->abajo->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar->abajo->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"[dir=both rankdir=UD];\n");
                    
            }
 
//------------------------------------NODOS DE LA MATRIZ--------------------------------------

            NodoMatriz* auxiliar2 = auxiliar->abajo;

            if(auxiliar2->abajo!=NULL){
                 do {
                   // cout<<"("<<auxiliar->x<<", "<<auxiliar->y<<", "<<auxiliar->letra<<") ";
                     strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar2->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar2->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"");

                     strcat(grafo,"->");

                      strcat(grafo,"\"(");
                     sprintf(num, "%d",auxiliar2->abajo->x);
                     strcat(grafo,num);
                     strcat(grafo,",");
                     sprintf(num, "%d",auxiliar2->abajo->y);
                     strcat(grafo,num);
                     strcat(grafo,")\"[dir=both rankdir=UD];\n");

                    auxiliar2 = auxiliar2->abajo;
                }while (auxiliar2->abajo!=NULL);
            }
            strcat(grafo,"\n");
            //cout<<"\n";
            temp = temp->siguiente;
        }     
    }
   }else{
        strcat(grafo,"{rank=min;");
        strcat(grafo,"\"ROOT\";};");
   }


     strcat(grafo,"}");
    FILE* fichero;
    fichero=fopen("/home/ulysses/Escritorio/Proyecto/Reportes/Scrabble.dot","wt");
    fputs(grafo,fichero);
    fclose(fichero);
    system("dot -Tpng /home/ulysses/Escritorio/Proyecto/Reportes/Scrabble.dot -o /home/ulysses/Escritorio/Proyecto/Reportes/Scrabble.png");
    //system("eog Reportes/Scrabble.png");
    //system("nohup display /home/rikardo/Documentos/Lista.png &" );

}






void Matriz::GraficarMatriz(NodoMatriz *raiz){

    NodoMatriz * ecolumna=raiz->siguiente;
    NodoMatriz * efila= raiz->abajo;


    char grafo[300000]="digraph G{\n node[shape=box, style=filled, color=lightskyblue]; \n edge[color=black];\nrankdir=UD;";
    char num[5000]="";


    if(ecolumna!=NULL && efila!=NULL){
        strcat(grafo,"{rank=min;");
        strcat(grafo,"\"Matriz\";");
        while (ecolumna!=NULL) {  //Si existen culumnas, hasta que llegue al final de las cabeceras
            strcat(grafo,"\"x");
            sprintf(num, "%d",ecolumna->id);
            strcat(grafo,num);
            strcat(grafo,"\"; ");
            ecolumna=ecolumna->siguiente;
    } // =======================================================================
    strcat(grafo,"};\n");
    while (efila!=NULL) {  //Si existen filas 
        NodoMatriz * temp=efila->siguiente;
        strcat(grafo,"{rank=same;");
        strcat(grafo,"\"y");
        sprintf(num, "%d",efila->id);
        strcat(grafo,num);
        strcat(grafo,"\";");
        while (temp!=NULL) {
            strcat(grafo,"\"xy:(");
            sprintf(num, "%d",temp->x);
            strcat(grafo,num);
            strcat(grafo,",");
            sprintf(num, "%d",temp->y);
            strcat(grafo,num);
             strcat(grafo,")\";");
             temp=temp->siguiente;
        }
        strcat(grafo,"};\n");
        efila=efila->abajo;
    } //===========================================================================

    efila = raiz-> abajo; 
    while (efila!=NULL) {
        NodoMatriz* temp=efila->siguiente;
        strcat(grafo,"\"y");
        sprintf(num, "%d",efila->id);
        strcat(grafo,num);
        strcat(grafo,"\"");
        strcat(grafo,"->");
        strcat(grafo,"\"xy:(");
        sprintf(num, "%d",efila->siguiente->x);
        strcat(grafo,num);
        strcat(grafo,",");
        sprintf(num, "%d",efila->siguiente->y);
        strcat(grafo,num);
        strcat(grafo,")\"[constraint=false];\n");

       strcat(grafo,"\"xy:(");
       sprintf(num, "%d",efila->siguiente->x);
       strcat(grafo,num);
       strcat(grafo,",");
       sprintf(num, "%d",efila->siguiente->y);
       strcat(grafo,num);
       strcat(grafo,")\"");
       strcat(grafo,"->");
       strcat(grafo,"\"y");
       sprintf(num, "%d",efila->id);
       strcat(grafo,num);
       strcat(grafo,"\"[constraint=false] ;\n");

       //======================================= Revisar arriba si falla
        while (temp->siguiente!=NULL) {

            strcat(grafo,"\"xy:(");
            sprintf(num, "%d",temp->x);
            strcat(grafo,num);
            strcat(grafo,",");
            sprintf(num, "%d",temp->y);
            strcat(grafo,num);
            strcat(grafo,")\"");

            strcat(grafo,"->");

            strcat(grafo,"\"xy:(");
            sprintf(num, "%d",temp->siguiente->x);
            strcat(grafo,num);
            strcat(grafo,",");
            sprintf(num, "%d",temp->siguiente->y);
            strcat(grafo,num);
            strcat(grafo,")\"[constraint=false];\n");

            if(temp->anterior->x != -1){
               strcat(grafo,"\"xy:(");
                sprintf(num, "%d",temp->x);
                strcat(grafo,num);
                strcat(grafo,",");
                sprintf(num, "%d",temp->y);
                strcat(grafo,num);
                strcat(grafo,")\"");
                strcat(grafo,"->");
                strcat(grafo,"\"xy:(");
                sprintf(num, "%d",temp->anterior->x);
                strcat(grafo,num);
                strcat(grafo,",");
                sprintf(num, "%d",temp->anterior->y);
                strcat(grafo,num);
                strcat(grafo,")\"[constraint=false];\n");
            }
            temp=temp->siguiente;
        }
       if(temp!=NULL && temp->anterior->x!=-1){
           strcat(grafo,"\"xy:(");
           sprintf(num, "%d",temp->x);
           strcat(grafo,num);
           strcat(grafo,",");
           sprintf(num, "%d",temp->y);
           strcat(grafo,num);
           strcat(grafo,")\"");
           strcat(grafo,"->");
            strcat(grafo,"\"xy:(");
           sprintf(num, "%d",temp->anterior->x);
           strcat(grafo,num);
           strcat(grafo,",");
           sprintf(num, "%d",temp->anterior->y);
           strcat(grafo,num);
           strcat(grafo,")\"[constraint=false];\n");
       }
        efila=efila->abajo; // ya cambié el "siguiente"
    }

//====================================================================================

    ecolumna = raiz ->siguiente;

    while (ecolumna->siguiente!=NULL) {
        strcat(grafo,"\"x");
        sprintf(num, "%d",ecolumna->id);
        strcat(grafo,num);
        strcat(grafo,"\"");
        strcat(grafo,"->");
        strcat(grafo,"\"x");
        sprintf(num, "%d",ecolumna->siguiente->id);
        strcat(grafo,num);
        strcat(grafo,"\";\n");
        ecolumna=ecolumna->siguiente;
    }
    while (ecolumna->anterior->x!=-1) { // Ya que hay una cabecera al final
        strcat(grafo,"\"x");
        sprintf(num, "%d",ecolumna->id);
        strcat(grafo,num);
        strcat(grafo,"\"");
        strcat(grafo,"->");
        strcat(grafo,"\"x");
        sprintf(num, "%d",ecolumna->anterior->id);
        strcat(grafo,num);
        strcat(grafo,"\";\n");
        if(ecolumna->siguiente!=NULL){
            strcat(grafo,"\"x");
            sprintf(num, "%d",ecolumna->id);
            strcat(grafo,num);
            strcat(grafo,"\"");
            strcat(grafo,"->");
            strcat(grafo,"\"x");
            sprintf(num, "%d",ecolumna->siguiente->id);
            strcat(grafo,num);
            strcat(grafo,"\"[constraint=false];\n");
        }
        ecolumna=ecolumna->anterior;
    }
   /* if(ecolumna!=NULL && ecolumna->siguiente!=NULL){
        strcat(grafo,"\"x");
        sprintf(num, "%d",ecolumna->id);
        strcat(grafo,num);
        strcat(grafo,"\"");
        strcat(grafo,"->");
        strcat(grafo,"\"x");
        sprintf(num, "%d",ecolumna->siguiente->id);
        strcat(grafo,num);
        strcat(grafo,"\"[constraint=false];\n");
    } */


    //////////////////////////////////////////////////////////////////////////////////////
    ecolumna=raiz->siguiente;
    if(ecolumna!=NULL){

        strcat(grafo,"Matriz");
        strcat(grafo,"->");
        strcat(grafo,"x");
        sprintf(num, "%d",ecolumna->id);
        strcat(grafo,num);
        strcat(grafo,"\n");
        strcat(grafo,"x");
        sprintf(num, "%d",ecolumna->id);
        strcat(grafo,num);
        strcat(grafo,"->");
        strcat(grafo,"Matriz");
        strcat(grafo,"[constraint=false];\n");
    }

// ================================= LO MISMO PERO CON LAS FILAS ?

    efila=raiz->abajo;

        if(efila!=NULL){
            strcat(grafo,"\"Matriz\"");
            strcat(grafo,"->");
            strcat(grafo,"\"y");
            sprintf(num, "%d",efila->id);
            strcat(grafo,num);
            strcat(grafo,"\"[rankdir=UD];\n");
            strcat(grafo,"\"y");
            sprintf(num, "%d",efila->id);
            strcat(grafo,num);
            strcat(grafo,"\"");
            strcat(grafo,"->");

        }
        while (efila->abajo!=NULL) {
            strcat(grafo,"\"y");
            sprintf(num, "%d",efila->id);
            strcat(grafo,num);
            strcat(grafo,"\"");
            strcat(grafo,"->");
            strcat(grafo,"\"y");
            sprintf(num, "%d",efila->abajo->id);
            strcat(grafo,num); 
            strcat(grafo,"\"[rankdir=UD];\n");
            if(efila->arriba->y!=-1){
                strcat(grafo,"\"y");
                sprintf(num, "%d",efila->id);
                strcat(grafo,num);
                strcat(grafo,"\"");
                strcat(grafo,"->");

                strcat(grafo,"\"y");
                sprintf(num, "%d",efila->arriba->id);
                strcat(grafo,num);
                strcat(grafo,"\"[rankdir=UD constraint=false];\n");
            
                
            }
            efila=efila->abajo;
        }
        if(efila->arriba->y!=-1){
            strcat(grafo,"\"y");
            sprintf(num, "%d",efila->id);
            strcat(grafo,num);
            strcat(grafo,"\"");
            strcat(grafo,"->");
             strcat(grafo,"\"y");
                sprintf(num, "%d",efila->arriba->id);
                strcat(grafo,num);
       
            strcat(grafo,"\"[rankdir=UD constraint=false];\n");
        }

        //============================================================================

        ecolumna=raiz->siguiente;
        while (ecolumna!=NULL) {
            NodoMatriz* temp=ecolumna->abajo;
            strcat(grafo,"\"x");
            sprintf(num, "%d",ecolumna->id);
            strcat(grafo,num);
            strcat(grafo,"\"");
            strcat(grafo,"->");
            strcat(grafo,"\"xy:(");
            sprintf(num, "%d",ecolumna->abajo->x);
            strcat(grafo,num);
            strcat(grafo,",");
            sprintf(num, "%d",ecolumna->abajo->y);
            strcat(grafo,num);
            strcat(grafo,")\"[rankdir=UD];\n");
            strcat(grafo,"\"xy:(");
            sprintf(num, "%d",ecolumna->abajo->x);
            strcat(grafo,num);
            strcat(grafo,",");
            sprintf(num, "%d",ecolumna->abajo->y);
            strcat(grafo,num);
            strcat(grafo,")\"");
            strcat(grafo,"->");
            strcat(grafo,"\"x");
            sprintf(num, "%d",ecolumna->id);
            strcat(grafo,num);
            strcat(grafo,"\"[rankdir=UD];\n");
            while (temp->abajo!=NULL) {
                 strcat(grafo,"\"xy:(");
                sprintf(num, "%d",temp->x);
                strcat(grafo,num);
                strcat(grafo,",");
                sprintf(num, "%d",temp->y);
                strcat(grafo,num);
                strcat(grafo,")\"");
                strcat(grafo,"->");
                 strcat(grafo,"\"xy:(");
                sprintf(num, "%d",temp->abajo->x);
                strcat(grafo,num);
                strcat(grafo,",");
                sprintf(num, "%d",temp->abajo->y);
                strcat(grafo,num);
                strcat(grafo,")\"[rankdir=UD];\n");
                if(temp->arriba->y!=-1){
                    strcat(grafo,"\"xy:(");
                    sprintf(num, "%d",temp->x);
                    strcat(grafo,num);
                    strcat(grafo,",");
                    sprintf(num, "%d",temp->y);
                    strcat(grafo,num);
                    strcat(grafo,")\"");
                    strcat(grafo,"->");
                    strcat(grafo,"\"xy:(");
                    sprintf(num, "%d",temp->arriba->x);
                    strcat(grafo,num);
                    strcat(grafo,",");
                    sprintf(num, "%d",temp->arriba->y);
                    strcat(grafo,num);
                    strcat(grafo,")\"[rankdir=UD];\n");
                }
                temp=temp->abajo;
            }
           if(temp!=NULL && temp->arriba->y!=-1){
               strcat(grafo,"\"xy:(");
               sprintf(num, "%d",temp->x);
               strcat(grafo,num);
               strcat(grafo,",");
               sprintf(num, "%d",temp->y);
               strcat(grafo,num);
               strcat(grafo,")\"");
               strcat(grafo,"->");
              strcat(grafo,"\"xy:(");
               sprintf(num, "%d",temp->arriba->x);
               strcat(grafo,num);
               strcat(grafo,",");
               sprintf(num, "%d",temp->arriba->y);
               strcat(grafo,num);
               strcat(grafo,")\"[rankdir=UD];\n");
           }
            ecolumna=ecolumna->siguiente;
        }
    }else{
        strcat(grafo,"{rank=min;");
        strcat(grafo,"\"Matriz\";};");
    }
    strcat(grafo,"}");
    FILE* fichero;
    fichero=fopen("/home/ulysses/Escritorio/Matriz.dot","wt");
    fputs(grafo,fichero);
    fclose(fichero);
    system("dot -Tpng /home/ulysses/Escritorio/Matriz.dot -o /home/ulysses/Escritorio/Matriz.png");
    //system("nohup display /home/rikardo/Documentos/Lista.png &" );
}