/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: programa que realiza 4 operaciones distintas usando hilos)
*/
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

struct hilos_aleatorios_parms{
	int contador;//randi
	int num; //index 
	string caracter = "paseme_profe";
	int a =50, b = 100;
	int c;
	string ruta = "pruebas.txt";
}; //hilos

int aleatorios[4];

void* mensaje(void* parametros){
	struct hilos_aleatorios_parms* p = (struct hilos_aleatorios_parms*) parametros;
 	cout << "El mensaje de mis numeros es: " << p->caracter << endl;
	return NULL;
}

void* SUMAR(void* parametros){
	struct hilos_aleatorios_parms* p = (struct hilos_aleatorios_parms*) parametros;
 	int resultado = p->a + p->b;
 	cout <<"El resultado es: " << resultado << endl;
	return NULL;
}


//funcion que leera la estructura con punteros
void* hilos_aleatorios(void* parametros){
	struct hilos_aleatorios_parms* p = (struct hilos_aleatorios_parms*) parametros;
	int cont = p->num;
	srand(time(NULL) + cont);
	aleatorios[cont] = (rand() % p->contador) + 1;
	cout<<"El numero elegido es: "<<cont<<aleatorios[cont]<< endl;
	cont++;
	return NULL;
}

void* leer_archivos(void* parametros){

	struct hilos_aleatorios_parms* p = (struct hilos_aleatorios_parms*) parametros;
	string filename=p->ruta;
    	ifstream archivo(filename); 
    	if (!archivo.is_open()) { // Verifica que el archivo se haya abierto 
        cout << "No se pudo abrir el archivo" << endl;
    	}
   	string linea;
    	while (getline(archivo, linea)) { // Lee cada línea del archivo
        	cout <<"El mensaje es este "<< linea << endl;
   	 }

    	archivo.close(); // Cierra el archivo
  
	return NULL;

}

int main(){
	pthread_t thread_id[4];
	
	struct hilos_aleatorios_parms thread_args[4];
	//struct hilos_aleatorios_parms mensaje[4];
	int i;
	for (i = 0; i< 4; i++){
		thread_args[i].contador = 10; //indica los numeros que apareceran
		thread_args[i].num = i; //indice del arreglo
	}//for
	
	pthread_create(&thread_id[0], NULL, hilos_aleatorios, &thread_args[0]);
	pthread_create(&thread_id[1], NULL, leer_archivos, &thread_args[1]);
	pthread_create(&thread_id[2], NULL, SUMAR, &thread_args[2]);
	pthread_create(&thread_id[3], NULL, mensaje, &thread_args[3]);
	//pthread_create(&thread_id[3], NULL, hilos_aleatorios, &mensaje[3]);

	//pthread_join (thread_id[0], NULL);
	//pthread_join (thread_id[1], NULL);
	//pthread_join (thread_id[2], NULL);
	//pthread_join (thread_id[3], NULL);
	
	int suma = 0;
	for (i = 0; i < 4; i++){
		suma += aleatorios[i];
	}
	pthread_exit(NULL);
	
	
	
	return 0;
}
