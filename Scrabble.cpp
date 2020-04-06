#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<fstream>      
#include<typeinfo>
//#include<ctime>
#include<unistd.h>
#include<time.h>

//#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include "json.hpp"
#include "Diccionario.h"
#include "Fichas.h"
#include "Usuarios.h"
#include "Scores.h"
#include "FichasJuego.h"
#include "Tablero.h"


using namespace std;
using json = nlohmann::json;


ListaDoble Diccionario;     //-
Cola       Fichas;          //-
Arbol      Usuarios;        // -
Lista      ScoreBoard;      // -
//Lista      Historial;       // **
//Doble      FichasJugador;   //-
Matriz     Tablero;         //-

int dimension;
int Filas[7];
int Columnas[7];
int cont = 0;
int Numero_turno = 0;
NodoUs *JugadorActual;


void Menu();
//============================================================

  void MostrarArchivo();
  void CargarArchivo();
  void AgregarJugador();
  void CargarDenuevo();

  void Jugar();

      void CargarCola();

      //Partida    
        void SeleccionarJugadores();
        void AsignarFichas(NodoUs *Jugador1, NodoUs *Jugador2);
        void Turno(NodoUs *J1, NodoUs *J2);
            void CambiarFichas(NodoUs *jugador);
            void AgregarFicha(NodoUs *jugador);
            void RemoverFicha(int x, int y, NodoUs *jugador);

   bool Colindancias(int x_i, int y_i, int x_f, int y_f, int turno, int sentido); //0:hor, 1:vert

   bool VerificarPalabras(int x_i, int y_i, int x_f, int y_f, int sentido); 

   void TerminarPartida(NodoUs *J1, NodoUs *J2);

  void Reportes();





 




int main(){  
  
  Usuarios.Insertar(Usuarios.raiz, -1, "Ulysses", NULL);
  Usuarios.Insertar(Usuarios.raiz, -1, "Orlando", NULL);
  
  CargarArchivo();

  Menu();
  cout<<"Salió";
  getchar();

  return 0;
}



void Menu(){

    int resp;
    system("clear");
    
      

      
      std::cout<< "\t .........................::-- M E N U --::......................... \n";

      cout<<"1. [Leer archivo] \n";
      cout<<"2. [Jugar]\n";
      cout<<"3. [Reportes]\n";
      cout<<"4. [Salir]\n";
  
      cout<<"Opcion: ";
      cin>>resp;
      
      
      switch(resp){
          case 1:
            system("clear");
            CargarDenuevo();
            cout<<"---Archivo cargado exitosamente---\n";
          break;
          case 2: 
             system("clear");
             Jugar();      
             break;
          case 3:
              system("clear");
              Reportes();
              Menu();
          break;
      }
     
    
    system("clear");
}


void Jugar(){

    int resp;
  
    
      
      cout<< "\t ....................::-- S C R A B B L E --::..................... \n";

      cout<<"1. [Iniciar Partida] \n";
      cout<<"2. [Agregar Jugador]\n";
      cout<<"3. [Regresar]\n";
  
      cout<<"Opción: ";
      cin>>resp;
      
      
      switch(resp){
          case 1:
              system("clear");
              CargarCola();
              Fichas.Graficar();
              SeleccionarJugadores();
          break;

          case 2: 
              system("clear");
              AgregarJugador();
             
             break;
           
          case 3:
            system("clear");
            Menu();
          break;
      }
     
    
}



           
 void SeleccionarJugadores(){
  
   string resp;
   NodoUs *Jugador1, *Jugador2;

    if (Usuarios.MinimoU()){
         cout<<"::::::::::::::::::::::Seleccionar Jugadores::::::::::::::::::"<<endl;
        Usuarios.Mostrar(Usuarios.raiz);
        cout<<"Jugador 1 [Ingrese el nombre]: "<<endl;
        cin>>resp;
        Jugador1 = Usuarios.BuscarNodo(Usuarios.raiz, resp);
        cout<<"Jugador 2 [Ingrese el nombre]: "<<endl;
        cin>>resp;
        Jugador2 = Usuarios.BuscarNodo(Usuarios.raiz, resp);
           if (Jugador2 != Jugador1){
             cout<<"...Asignando fichas..."<<endl;
             AsignarFichas(Jugador1, Jugador2);
           } else {
             cout<<"\n\nEl jugador 1 no puede ser igual que el jugador 2.\nSeleccione de nuevo";
             SeleccionarJugadores();
           }
        } else {
        cout<<"No hay suficientes jugadores registrados"<<endl;
        Jugar();
       }
  }

void AgregarJugador(){
  string nombre;
    cout<<"Crear nuevo jugador"<<endl;
    cout<<"Ingrese su nombre:  ";
    cin>>nombre;
    Usuarios.Insertar(Usuarios.raiz, -1, nombre, NULL);
    Jugar();
}

void VerPuntajes(){

}

void AsignarFichas(NodoUs *J1, NodoUs *J2){
   cout<<"[---Asignando fichas---]"<<endl;

for (int i=0; i<7; i++){
   NodoD * f = Fichas.Eliminar();
   Usuarios.InsertarFicha(J1, f);
}

for (int i=0; i<7; i++){
   NodoD * f = Fichas.Eliminar();
   Usuarios.InsertarFicha(J2, f);
}


Turno(J1, J2);

}



//===================================================T U R N O==========================================
void Turno(NodoUs *J1, NodoUs *J2){
  
  int opc;
  string nombre;
  
  if (Numero_turno == 0){
      srand(time(0)*rand()%10);
      int az = 1+ rand()%(2);
      cout<<"Numero al azar entre 1 y 2: "<<az<<endl;
      if (az == 1){
        JugadorActual = J1;
        nombre = JugadorActual->nombre;
        Numero_turno++;
      }
      else if (az==2){
        JugadorActual = J2;
        nombre = JugadorActual->nombre;
        Numero_turno++;
      } else {
        cout<<"Se generó un numero distinto a 1 o 2"<<endl;
      }
  } else {
    nombre = JugadorActual->nombre;
  }
  
  Usuarios.GraficarFichas(JugadorActual);
  //system("clear");
  cout<<"\n\nTurno #"<<Numero_turno<<": Juega "<<nombre<<"!"<<endl;
  cout<<"El contador es: "<<cont<<endl;
  cout<<"\n\n...................::::Opciones::::......................"<<endl;
  cout<<"\n1. Colocar ficha"<<endl;
  cout<<"2. Cambiar fichas"<<endl;
  cout<<"3. Jugar "<<endl;
  cout<<"4. Rendirse"<<endl;
  cout<<"5. Reportes"<<endl;
  cout<<"\nOpción: ";
  cin>>opc;

  if(opc==1){
    AgregarFicha(JugadorActual);
    Turno(J1, J2);  
  }else if(opc ==2){
    CambiarFichas(JugadorActual);
    Numero_turno++;
    if(JugadorActual == J1){
      JugadorActual = J2;
    } else if (JugadorActual ==J2){
      JugadorActual = J1;
    }
    Turno(J1, J2);  
  }else if(opc==3){
    
    //Aqui se verifica 

    bool c_iguales = true;
    bool f_iguales = true;
    int x_mandar, y_mandar;

    cout<<"contador: "<<cont<<endl;
  
    for (int i=0; i<cont; i++){ //Mostrando columnas
     cout<<"C:"<<Columnas[i]<<"\n";
    }
  
    for (int i=0; i<cont; i++){ //Mostrando filas
      cout<<"F:"<<Filas[i]<<"\n";
    } 

    for (int i=0; i<cont-1; i++){ //Revisar si las columnas son iguales 
       if(Columnas[i] != Columnas[i+1]){
           c_iguales = false;
           cout<<Columnas[i]<<" != "<<Columnas[i+1]<<endl;
         } 

    }
  cout<<"columnas iguales? "<<c_iguales<<endl;

    for (int i=0; i<cont-1; i++){ //Revisar si las filas son iguales
         if(Filas[i] != Filas[i+1]){
           f_iguales = false;
           cout<<Filas[i]<<" != "<<Filas[i+1]<<endl;
         }
    } //Fin for
  cout<<"filas iguales? "<<f_iguales<<endl;

    int mayor=0, menor, i;



    if(f_iguales == true){ //Si todas las filas son iguales, la palabra está en horizontal

    	  for(i=0;i<cont;i++){
	   if(mayor<Columnas[i])
		 mayor=Columnas[i];
	  }

	  menor=mayor;

	  for(i=0;i<cont;i++){
      if(menor>Columnas[i])
		  menor=Columnas[i];
    }

    cout<<"Mayor: "<<mayor<<endl;
    cout<<"Menor: "<<menor<<endl;

    if(Colindancias(menor, Filas[0], mayor, Filas[0], Numero_turno, 0)){
    cout<<"Bien jugado!"<<endl;
    if(!Fichas.Cola_Vacia(Fichas.frente)){
        
        if(Fichas.contar()>cont){
           for(int i=0; i<cont;i++){
       NodoD * f = Fichas.Eliminar();
       Usuarios.InsertarFicha(JugadorActual, f);
         } 
        } else{
            for(int i=0; i<Fichas.contar();i++){
       NodoD * f = Fichas.Eliminar();
       Usuarios.InsertarFicha(JugadorActual, f);
         } 
        }
        
      cout<<"Elementos en la cola: "<<Fichas.contar();
    } else{ 
      cout<<"La cola ya está vacía"<<endl;
    }
  
    } else{
     cout<<"Mal colocada o no válida hor"<<endl;
      for(int i=0; i<cont;i++){
        x_mandar = Columnas[i];
        y_mandar = Filas[i];
        RemoverFicha(x_mandar, y_mandar, JugadorActual);
      }
    }
    Numero_turno++;
    if(JugadorActual == J1){
      JugadorActual = J2;
    } else if (JugadorActual ==J2){
      JugadorActual = J1;
    }
      //Vaciar arreglos
  for (int i=0; i<=cont; i++){
    Columnas[i] = 0;
  }
  for (int i=0; i<=cont; i++){
    Filas[i] = 0;
  }
  cont = 0;
    Turno(J1, J2);


  } else if(c_iguales == true){ //Si todas las columnas son iguales, la palabra está en vertical

	  for(i=0;i<cont;i++){
	   if(mayor<Filas[i])
		 mayor=Filas[i];
	  }

	  menor=mayor;

	  for(i=0;i<cont;i++){
      if(menor>Filas[i])
		  menor=Filas[i];
    }

    cout<<"Mayor: "<<mayor<<endl;
    cout<<"Menor: "<<menor<<endl;

   if(Colindancias(Columnas[0], menor, Columnas[0], mayor, Numero_turno, 1)){
    cout<<"Bien jugado!"<<endl;
    if(!Fichas.Cola_Vacia(Fichas.frente)){
        
        if(Fichas.contar()>cont){
           for(int i=0; i<cont;i++){
       NodoD * f = Fichas.Eliminar();
       Usuarios.InsertarFicha(JugadorActual, f);
         } 
        } else{
            for(int i=0; i<Fichas.contar();i++){
       NodoD * f = Fichas.Eliminar();
       Usuarios.InsertarFicha(JugadorActual, f);
         } 
        }
        
      cout<<"Elementos en la cola: "<<Fichas.contar();
    } else{ 
      cout<<"La cola ya está vacía"<<endl;
    }
    } else{
     cout<<"Mal colocada o no válida"<<endl;
      for(int i=0; i<cont;i++){
        x_mandar = Columnas[i];
        y_mandar = Filas[i];
        RemoverFicha(x_mandar, y_mandar, JugadorActual);
      }
    }

    Numero_turno++;
    if(JugadorActual == J1){
      JugadorActual = J2;
    } else if (JugadorActual ==J2){
      JugadorActual = J1;
    }
      //Vaciar arreglos
  for (int i=0; i<=cont; i++){
    Columnas[i] = 0;
  }
  for (int i=0; i<=cont; i++){
    Filas[i] = 0;
  }
  cont = 0;
    Turno(J1, J2);
     
  } else { //devolver fichas
     cout<<"Fichas mal posicionadas :("<<endl;
        for(int i=0; i<cont;i++){
        x_mandar = Columnas[i];
        y_mandar = Filas[i];
        RemoverFicha(x_mandar, y_mandar, JugadorActual);
      }

    Numero_turno++;
    if(JugadorActual == J1){
      JugadorActual = J2;
    } else if (JugadorActual ==J2){
      JugadorActual = J1;
    }
        //Vaciar arreglos
  for (int i=0; i<=cont; i++){
    Columnas[i] = 0;
  }
  for (int i=0; i<=cont; i++){
    Filas[i] = 0;
  }
  cont = 0;
    Turno(J1, J2);
  }

  }
  else if(opc==4){
    TerminarPartida(J1, J2);
  }
  else if(opc==5){
    Reportes();
    Turno(J1, J2);
  }
  
 }

 void TerminarPartida(NodoUs *J1, NodoUs *J2){
    system("clear");
    Usuarios.InsertarScore(J1, J1->acumulado);
    Usuarios.InsertarScore(J2, J2->acumulado);

    Usuarios.GraficarScores(J2);

    cout<<"Puntaje de "<<J1->nombre<<": "<<J1->acumulado<<endl;
    cout<<"Puntaje de "<<J2->nombre<<": "<<J2->acumulado<<endl;

    if(J1->acumulado > J2->acumulado){
      cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~ "<<J1->nombre<<" gana! ~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    } else if (J1->acumulado < J2->acumulado){
      cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~ "<<J2->nombre<<" gana! ~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    } else {
      cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~ Empate ~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    }

    ScoreBoard.Insertar(J1->nombre, J1->Historial.lista->punteo);
    ScoreBoard.Insertar(J2->nombre, J2->Historial.lista->punteo);
    ScoreBoard.GraficarGlobal();
    sleep(2);
    //Borrar el tablero, borrar las listas de los jugadores 
    Tablero.VaciarMatriz(Tablero.raiz);
    Tablero.Graficar();
    //Resetear dimensión
    dimension = 0;
    //Vaciar lista de jugadores 
    Usuarios.MostrarLista(J1);
    Usuarios.MostrarLista(J1);
    Usuarios.VaciarLJ(J1);
    Usuarios.VaciarLJ(J2);
    //Vaciar cola 
    Fichas.Vaciar();
    sleep(2);
    Menu();
 }



void CambiarFichas(NodoUs *jugador){
  char letra;
  int resp;
  
  if (Fichas.frente!=Fichas.fin){

  do{
 cout<<"1. Cambiar ficha"<<endl;
 cout<<"2. Terminar"<<endl;
 cout<<"Opcion: ";
    cin>>resp;
   switch (resp)
   {
   case 1:
      cout<<"Ingrese la letra que desea cambiar"<<endl;
      cin>>letra;
      NodoD * ficha = jugador->Fichas.Eliminar(letra);
      Fichas.Insertar(ficha->id, ficha->valor, ficha->letra);
      NodoD * fichaCola = Fichas.Eliminar();
      Usuarios.InsertarFicha(jugador, fichaCola);
      
      Usuarios.GraficarFichas(jugador);
      Fichas.Graficar();
     break;
 
   }
     
  } while(resp!=2);
   
  } else {
        cout<<"Ya no se pueden cambiar fichas, la cola está vacía"<<endl;
  }
  
 }



void AgregarFicha(NodoUs *jugador){
  
  int x, y;
  char letra;
  //Usuarios.GraficarFichas(jugador);
  
    cout<<"Ingrese coordenadas para la ficha"<<endl;
    cout<<"x: ";
    cin>>x;
    cout<<"y: ";
    cin>>y;

    cout<<"Ingrese la letra a colocar: "<<endl;
    cin>>letra;

    NodoD * ficha = jugador->Fichas.Eliminar(toupper((int)letra));
    
if(ficha!=NULL){
  if (Tablero.BuscarNodo(x,y)==NULL){ //Si no existe el nodo, agregar
     Tablero.Insertar(x, y, letra, ficha->valor, ficha->id, false, false, false, false, ficha->ide);
     Columnas[cont] = x;
      Filas[cont] = y;
      Tablero.Graficar();
      
  } else { //Si existe, verificar si es doble o triple / O una casilla ya utilizada 
    NodoMatriz * existente = Tablero.BuscarNodo(x, y);
    if (existente->dob == true){
        Tablero.EliminarNodo(x,y);
        Tablero.Insertar(x, y, letra, ficha->valor, ficha->id, false, false, true, false, ficha->ide);
       Columnas[cont] = x;
        Filas[cont] = y;
        Tablero.Graficar();
       
    } else if(existente->tri == true){
        Tablero.EliminarNodo(x,y);
        Tablero.Insertar(x, y, letra, ficha->valor, ficha->id, false, false, false, true, ficha->ide);
        Columnas[cont] = x;
        Filas[cont] = y;
        Tablero.Graficar();
      
    } else {
      cout<<"----Casilla ya utilizada----"<<endl;
      AgregarFicha(jugador);
    }
  }
} 
 cont++;
 }


void RemoverFicha(int x, int y, NodoUs *jugador){
  NodoMatriz * ficha = Tablero.EliminarNodo(x,y);
if(ficha!=NULL){
  if (ficha->t == true){
    Tablero.Insertar(x, y, 'T', -1, 0, false, true, false,false, "triple");
    jugador->Fichas.Insertar(ficha->id, ficha->valor, ficha->letra);
    Usuarios.GraficarFichas(jugador);
    Tablero.Graficar();
  } else if(ficha->d == true){
    Tablero.Insertar(x, y, 'D', -1, 0, true, false, false,false, "doble");
    jugador->Fichas.Insertar(ficha->id, ficha->valor, ficha->letra);
    Usuarios.GraficarFichas(jugador);
    Tablero.Graficar();
  } else {
    jugador->Fichas.Insertar(ficha->id, ficha->valor, ficha->letra);
    Usuarios.GraficarFichas(jugador);
    Tablero.Graficar();
  }
 }
}

bool VerificarPalabras(int x_i, int y_i, int x_f, int y_f, int sentido){
    cout<<"INICIO VERIFICAR PALABRA: "<<x_i<<", "<<y_i<<endl;
    cout<<"FIN VERIFICAR PALABRA: "<<x_f<<", "<<y_f<<endl;
    //return true;
    NodoMatriz * ini = Tablero.BuscarNodo(x_i, y_i);
    NodoMatriz * fin = Tablero.BuscarNodo(x_f, y_f);
    NodoMatriz * auxiliar; 
    string palabra;

    int puntosPal = 0;

    if(sentido == 0){
      cout<<"Verificando palabra en horizontal"<<endl;
      int x = ini->x;
      auxiliar = ini;
        for(x; x<=fin->x; x++){
          cout<<"letra: "<<auxiliar->letra<<"->puntos:"<<auxiliar->valor;
          palabra.push_back(tolower(auxiliar->letra));

          if(auxiliar->d==true){
            puntosPal = puntosPal + auxiliar->valor * 2;
            cout<<"(2)"<<endl;
          }else if(auxiliar->t==true){
            puntosPal = puntosPal + auxiliar->valor * 3;
            cout<<"(3)"<<endl;
          }else{
            puntosPal = puntosPal + auxiliar->valor;
            cout<<"\n";
          }

          auxiliar = auxiliar->siguiente;
        }
        cout<<"Palabra: "<<palabra<<endl;
        cout<<"Puntos: "<<puntosPal<<endl;
        Usuarios.setAcumulado(JugadorActual, puntosPal);
        cout<<"Punteo acumulado: "<<JugadorActual->acumulado<<endl;
        //return true;
        return Diccionario.BuscarNodo(palabra);


    } else if (sentido == 1){
      cout<<"Verificando palabra en vertical"<<endl;
      int y = ini->y;
      auxiliar = ini;
        for(y; y<=fin->y; y++){
          cout<<"letra: "<<auxiliar->letra<<"->puntos:"<<auxiliar->valor<<endl;
          palabra.push_back(tolower(auxiliar->letra));
          if(auxiliar->d==true){
            puntosPal = puntosPal + auxiliar->valor * 2;
            cout<<"(2)"<<endl;
          }else if(auxiliar->t==true){
            puntosPal = puntosPal + auxiliar->valor * 3;
            cout<<"(3)"<<endl;
          }else{
            puntosPal = puntosPal + auxiliar->valor;
            cout<<"\n";
          }
          auxiliar=auxiliar->abajo;
        }  
        cout<<"Palabra: "<<palabra<<endl;
        cout<<"Puntos: "<<puntosPal<<endl;
        Usuarios.setAcumulado(JugadorActual, puntosPal);
        cout<<"Punteo acumulado: "<<JugadorActual->acumulado<<endl;
        //return true;
        return Diccionario.BuscarNodo(palabra);
    }
}

bool Colindancias(int x_i, int y_i, int x_f, int y_f, int turno, int sentido){
    NodoMatriz * inicio = Tablero.BuscarNodo(x_i, y_i);
    NodoMatriz * final = Tablero.BuscarNodo(x_f, y_f);
    cout<<"Revisará colindancia"<<endl;
    NodoMatriz * aux ;
    bool encontro = false;
    bool palabrabuena = true;
    if (turno == 1){
        return VerificarPalabras(x_i, y_i, x_f, y_f, sentido);
    } else {
        //sentido -> 0:hor, 1:vert
        if (sentido == 0){ // H O R I Z O N T A L
        
       
        //Encontar colindancia en los laterales 

       if (final->siguiente!=NULL){
            if(final->siguiente->valor!=-1 && inicio->anterior->valor!=-1){ //Colindancia en ambos 
              
              cout<<"encontró colindancia en ambos lados\n";
                
                  if(final->x+1 == final->siguiente->x && inicio->x == inicio->anterior->x+1){
                 encontro = true;
                 aux = final->siguiente; //Revisar hasta donde llega en la derecha 
                    x_f = aux->x;
                     y_f = aux->y;
                               
                 aux = inicio->anterior; //Revisar hasta donde llega en la izquierda
                x_i = aux->x;
                y_i = aux->y;
            
                
                if (!VerificarPalabras(x_i, y_i, x_f, y_f, 0)){
                    palabrabuena = false;
                }
                  }
           
            

            } else if(final->siguiente->valor!=-1){ //Colindancia en la derecha 
              if(final->x+1 == final->siguiente->x){
              aux = final->siguiente; //Revisar hasta donde llega en la derecha 
              encontro = true;
              cout<<"encontró colindancia en la derecha\n";
                x_f = aux->x;
                y_f = aux->y;
             
             if (!VerificarPalabras(x_i, y_i, x_f, y_f, 0)){
                    palabrabuena = false;;
                }
              }
            } else if (inicio->anterior->valor!= -1){ //Colindancia en la izquierda
             if(inicio->x == inicio->anterior->x+1){
      
            aux = inicio->anterior; //Revisar hasta donde llega en la izquierda
            encontro = true;
            cout<<"encontró colindancia en la izquierda\n";
                x_i = aux->x;
                y_i = aux->y;
            
            if (!VerificarPalabras(x_i, y_i, x_f, y_f, 0)){
                    palabrabuena = false;;
                }
           }
            }

        } else if (inicio->anterior->valor!= -1){ //Colindancia en la izquierda
           if(inicio->x == inicio->anterior->x+1){
            cout<<"colindancia en la izquierda"<<endl;
            aux = inicio->anterior; //Revisar hasta donde llega en la izquierda
            encontro = true;
            
                x_i = aux->x;
                y_i = aux->y;
            
            if (!VerificarPalabras(x_i, y_i, x_f, y_f, 0)){
                    palabrabuena = false;;
                }
        }  
        }
        

        //Encontrar colindancia arriba o abajo
        aux = inicio;
        int x = inicio->x;

      
        for(x; x<=final->x; x++){
                if( aux->abajo!= NULL){
                    if(aux->arriba->valor!= -1 && aux->abajo->valor!= -1){ //Caso 1, ambos lados
                    
                         if(aux->abajo->y == aux->y+1 && aux->arriba->y+1 == aux->y) {
                           palabrabuena = false;
                         } 
                            
                         
                    } else if(aux->abajo->valor!=-1){ //Caso 2, abajo
                    
                          if(aux->abajo->y == aux->y +1){
                            palabrabuena = false;
                          }
                        
                            
                        
                    } else if (aux->arriba->valor!=-1){ //Caso 3, arriba
                     
                    if (aux->arriba->y+1 == aux->y){
                      palabrabuena = false;
                    }
                            
                    
                 }
                } else if (aux->arriba->valor!=-1){ //Caso 3, arriba
                     
                    if (aux->arriba->y+1 == aux->y){
                      palabrabuena = false;
                    }
                    
                }
             
                aux = aux->siguiente;
        }
        if(!encontro){
          return false;
        }

        return palabrabuena;
      
     //--------------------------------------------------------------------------------

        } //Fin sentido horizontal 
        else if(sentido==1) {  //Sentido Vertical
        //Encontar colindancia en los laterales 
          cout<<"Revisar colindancia si viene vertical\n";
          if (final->abajo!=NULL){
            if(final->abajo->valor!=-1 && inicio->arriba->valor!=-1){ //Colindancia en ambos 
              
              if(final->abajo->y = final->y+1 && inicio->y == inicio->arriba->y+1){
              cout<<"encontró colindancia en ambos lados\n";
              encontro = true;
      
                aux = final->abajo; //abajo
                x_f = aux->x;
                y_f = aux->y;
             
                aux = inicio->arriba; //arriba
                x_i = aux->x;
                y_i = aux->y;
                       
                if (!VerificarPalabras(x_i, y_i, x_f, y_f, 1)){
                    palabrabuena = false;
                }
              }

            } else if(final->abajo->valor!=-1){ //Colindancia abajo
             if(final->y+1 == final->abajo->y){
              aux = final->abajo; //abajo
              encontro = true;
          
                x_f = aux->x;
                y_f = aux->y;
             
             if (!VerificarPalabras(x_i, y_i, x_f, y_f, 1)){
                    palabrabuena = false;
                }
             }
            } else if (inicio->arriba->valor!= -1){ //Colindancia arriba
            if(inicio->y == inicio->arriba->y+1){
            aux = inicio->arriba; //Revisar hasta donde llega arriba
            encontro = true;
            cout<<"encontró colindancia arriba\n";
                x_i = aux->x;
                y_i = aux->y;
            
            if (!VerificarPalabras(x_i, y_i, x_f, y_f, 1)){
                    palabrabuena = false;
                }
            }
          }
        } else if (inicio->arriba->valor!= -1){ //Colindancia arriba
          if(inicio->y == inicio->arriba->y+1){
            aux = inicio->arriba; //Revisar hasta donde llega arriba
            encontro = true;
            cout<<"encontró colindancia arriba\n";
                x_i = aux->x;
                y_i = aux->y;
            
            if (!VerificarPalabras(x_i, y_i, x_f, y_f, 1)){
                    palabrabuena = false;
                }
          }
        } 
        

        //Encontrar colindancia izq o der
        aux = inicio;
        int y = inicio->y;

        cout<<"INICIO de for: "<<x_i<<", "<<y<<endl;
        cout<<"FIN: "<<x_f<<", "<<final->y<<endl;

      
        for(y; y<=final->y; y++){
                if( aux->siguiente!= NULL){
                    if(aux->anterior->valor!= -1 && aux->siguiente->valor!= -1){ //Caso 1, ambos lados

                        if(aux->siguiente->x == aux->x+1 && aux->anterior->x +1 == aux->x ){
                          palabrabuena = false;
                        }
                            
                         
                    } else if(aux->siguiente->valor!=-1){ //Caso 2, derecha

                          if (aux->siguiente->x == aux->x+1)
                          {
                            palabrabuena = false;
                          }
                               
                    } else if (aux->anterior->valor!=-1){ //Caso 3, izquierda
                          if(aux->anterior->x +1 == aux->x){
                            palabrabuena = false;
                          }                        
                   }
                } else if (aux->anterior->valor!=-1){ //Caso 3, izquierda
                          if(aux->anterior->x +1 == aux->x){
                            palabrabuena = false;
                          }   
                }
             
                aux = aux->abajo;
        }
        if(!encontro){
          return false;
        }

        return palabrabuena;
       } 
    } //Si el turno no es uno ^ 
  
}


  void Reportes(){
    int resp;
    string usuario;
    NodoUs *us;
    system("clear");
    
      std::cout<< "\t ......................::-- R E P O R T E S --::...................... \n";

      cout<<"1. [Diccionario]\n";
      cout<<"2. [Fichas]\n";
      cout<<"3. [Usuarios]\n";
      cout<<"4. [Usuarios Pre-Orden]\n";
      cout<<"5. [Usuarios In-Orden]\n";
      cout<<"6. [Usuarios Post-Orden]\n";
      cout<<"7. [ScoreBoard]\n";
      cout<<"8. [Puntajes x Usario]\n";
      cout<<"9. [Fichas x Usuario]\n";
      cout<<"Opcion: ";
      cin>>resp;
      switch (resp)
      {
      case 1:
        Diccionario.Graficar();
        system("eog Reportes/Diccionario.png");
      break;

      case 2:
      Fichas.Graficar();
      system("eog Reportes/Cola.png");
      break;

      case 3:
      Usuarios.GraficarArbol();
      system("eog Reportes/ArbolU.png");
      break;

      case 4:
      Usuarios.GraPre();
      break;

      case 5:
      Usuarios.GraIn();
      break;

      case 6:
      Usuarios.GraPost();
      break;

      case 7:
      ScoreBoard.GraficarGlobal();
      system("eog Reportes/ScoreBoard.png");
      break;

      case 8:
      cout<<"Ingrese el nombre del usuario: ";
      cin>>usuario;
      us = Usuarios.BuscarNodo(Usuarios.raiz, usuario);
      Usuarios.InsertarScore(us, us->acumulado);
      Usuarios.GraficarScores(us);
      system("eog Reportes/HistorialJ.png");
      break;

      case 9:
      cout<<"Ingrese el nombre del usuario: ";
      cin>>usuario;
      us = Usuarios.BuscarNodo(Usuarios.raiz, usuario);
      Usuarios.GraficarFichas(us);
      system("eog Reportes/FJugador.png");
      break;
      default:
      break;
      }
  }




void CargarArchivo(){
  std::ifstream i("Entrada.json");
    json j3;
    i >> j3;

    dimension = j3.at("dimension");
    
   //_________________________________Diccionario _________________________________
    for(int x = 0; x < j3.at("diccionario").size(); x++)
    {   
        
        Diccionario.Insertar(j3.at("diccionario")[x].at("palabra"), x);
    }
    Diccionario.Graficar();
    
    //_______________________________Casillas dobles_______________________________
 
    for(int x = 0; x < j3.at("casillas").at("dobles").size(); x++)
    {
 
      Tablero.Insertar(j3.at("casillas").at("dobles")[x].at("x"), j3.at("casillas").at("dobles")[x].at("y"), 'D', -1, 0, true, false, false,false, "doble");
      cout<<"Se agregó Nodo: ["<<j3.at("casillas").at("dobles")[x].at("x")<<", "<<j3.at("casillas").at("dobles")[x].at("y")<<"]"<<endl;
    }

    //______________________________Casillas triples_______________________________

    for(int x = 0; x < j3.at("casillas").at("triples").size(); x++)
    {
      Tablero.Insertar(j3.at("casillas").at("triples")[x].at("x"), j3.at("casillas").at("triples")[x].at("y"), 'T', -1, 0, false, true, false, false, "triple");
      cout<<"Se agregó Nodo: ["<<j3.at("casillas").at("triples")[x].at("x")<<", "<<j3.at("casillas").at("triples")[x].at("y")<<"]"<<endl;
    }

    Tablero.GraficarMatriz(Tablero.raiz);
    Tablero.Graficar();
    cout<<"Archivo cargado exitosamente";
    Menu();
}

void CargarDenuevo(){
    std::ifstream i("Entrada.json");
    json j3;
    i >> j3;

    dimension = j3.at("dimension");
    
    //_______________________________Casillas dobles_______________________________
 
    for(int x = 0; x < j3.at("casillas").at("dobles").size(); x++)
    {
 
      Tablero.Insertar(j3.at("casillas").at("dobles")[x].at("x"), j3.at("casillas").at("dobles")[x].at("y"), 'D', -1, 0, true, false, false,false, "doble");
      cout<<"Se agregó Nodo: ["<<j3.at("casillas").at("dobles")[x].at("x")<<", "<<j3.at("casillas").at("dobles")[x].at("y")<<"]"<<endl;
    }

    //______________________________Casillas triples_______________________________

    for(int x = 0; x < j3.at("casillas").at("triples").size(); x++)
    {
      Tablero.Insertar(j3.at("casillas").at("triples")[x].at("x"), j3.at("casillas").at("triples")[x].at("y"), 'T', -1, 0, false, true, false, false, "triple");
      cout<<"Se agregó Nodo: ["<<j3.at("casillas").at("triples")[x].at("x")<<", "<<j3.at("casillas").at("triples")[x].at("y")<<"]"<<endl;
    }

    Tablero.GraficarMatriz(Tablero.raiz);
    Tablero.Graficar();
    cout<<"Archivo cargado exitosamente";
    Menu();
}







void MostrarArchivo(){
     std::ifstream i("Entrada.json");
    json j3;
    i >> j3;

    cout <<"Dimension: "<< j3.at("dimension")<<endl;

    cout <<"Casillas dobles: "<<endl;

    for(int x = 0; x < j3.at("casillas").at("dobles").size(); x++)
    {
      cout<<"palabra "<<x<<endl;
        cout << "X:  " << j3.at("casillas").at("dobles")[x].at("x") << endl;
        cout << "Y:  " << j3.at("casillas").at("dobles")[x].at("y") << endl;
    }
    cout <<"Casillas triples: "<<endl;
    for(int x = 0; x < j3.at("casillas").at("triples").size(); x++)
    {
      cout<<"palabra "<<x<<endl;
        cout << "X:  " << j3.at("casillas").at("triples")[x].at("x") << endl;
        cout << "Y:  " << j3.at("casillas").at("triples")[x].at("y") << endl;
    }

    for(int x = 0; x < j3.at("diccionario").size(); x++)
    {
        cout << "Palabra " << j3.at("diccionario")[x].at("palabra") << endl;
    }

}

void CargarCola(){
  int marcador = 95;
  int letra;
  int a = 12; int e = 12;
  int o = 9;
  int i = 6; int s = 6;
  int n = 5; int r = 5; int u = 5;
  int l = 4; int t = 4;
  
  
  int d = 5;
  int g = 2; 
  
  int b = 2; int m = 2; int p = 2;
  int c = 4;
  
  int h = 2;
  int f = 1;
  int v = 1;
  int y = 1;

  int q = 1;

  int j = 1;
  int enie = 1;
  int x = 1;

  int z = 1;
  
    while(marcador!=0){
      //sleep();
      srand(time(0)*rand()%10000);
      letra = 1+ rand()%(25);
      cout<<"Número: "<<letra<<endl;

      switch (letra)
      {
             case 1: //A 
        if(a!=0){
          Fichas.Insertar(a, 1, 'A');
          a--;
          marcador--;
        }
        break;
      case 2: //E
        if(e!=0){
          Fichas.Insertar(e, 1, 'E');
          e--;
          marcador--;
        }
        break;

      case 3: //O
        if(o!=0){
          Fichas.Insertar(o, 1, 'O');
          o--;
          marcador--;
        }
        break;

        case 4: //I
        if(i!=0){
          Fichas.Insertar(i, 1, 'I');
          i--;
          marcador--;
        }
        break;

        case 5: //S
        if(s!=0){
          Fichas.Insertar(s, 1, 'S');
          s--;
          marcador--;
        }
        break;

        case 6: //N
        if(n!=0){
          Fichas.Insertar(n, 1, 'N');
          n--;
          marcador--;
        }
        break;

        case 7: //L
        if(l!=0){
          Fichas.Insertar(l, 1, 'L');
          l--;
          marcador--;
        }
        break;

        case 8: //R
        if(r!=0){
          Fichas.Insertar(r, 1, 'R');
          r--;
          marcador--;
        }
        break;

        case 9: //U
        if(u!=0){
          Fichas.Insertar(u, 1, 'U');
          u--;
          marcador--;
        }
        break;

        case 10: //T
        if(t!=0){
          Fichas.Insertar(t, 1, 'T');
          t--;
          marcador--;
        }
        break;

        case 11: //D
        if(d!=0){
          Fichas.Insertar(d, 2, 'D');
          d--;
          marcador--;
        }
        break;

        case 12: //G
        if(g!=0){
          Fichas.Insertar(g, 2, 'G');
          g--;
          marcador--;
        }
        break;

        case 13: //C
        if(c!=0){
          Fichas.Insertar(c, 3, 'C');
          c--;
          marcador--;
        }
        break;

        case 14: //B
        if(b!=0){
          Fichas.Insertar(b, 3, 'B');
          b--;
          marcador--;
        }
        break;

        case 15: //M
        if(m!=0){
          Fichas.Insertar(m, 3, 'M');
          m--;
          marcador--;
        }
        break;

        case 16: //P
        if(p!=0){
          Fichas.Insertar(p, 3, 'P');
          p--;
          marcador--;
        }
        break;

        case 17: //H
        if(h!=0){
          Fichas.Insertar(h, 4, 'H');
          h--;
          marcador--;
        }
        break;

        case 18: //F
        if(f!=0){
          Fichas.Insertar(f, 4, 'F');
          f--;
          marcador--;
        }
        break;

        case 19: //V
        if(v!=0){
          Fichas.Insertar(v, 4, 'V');
          v--;
          marcador--;
        }
        break;

        case 20: //Y
        if(y!=0){
          Fichas.Insertar(y, 4, 'Y');
          y--;
          marcador--;
        }
        break;

        case 21: //Q
        if(q!=0){
          Fichas.Insertar(q, 5, 'Q');
          q--;
          marcador--;
        }
        break;

        case 22: //J
        if(j!=0){
          Fichas.Insertar(j, 8, 'J');
          j--;
          marcador--;
        }
        break;

        case 23: //Ñ
        if(enie!=0){
          Fichas.Insertar(enie, 8, 'K');
          enie--;
          marcador--;
        }
        break;

        case 24: //X
        if(x!=0){
          Fichas.Insertar(x, 8, 'X');
          x--;
          marcador--;
        }
        break;

        case 25: //Z
        if(z!=0){
          Fichas.Insertar(z, 10, 'Z');
          z--;
          marcador--;
        }
        break;



      default:
        break;

      }

    }



}
