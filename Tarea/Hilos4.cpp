/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Programa que posee 4 hilos a traves de un arreglo*/
#include <iostream>
#include <thread>

using namespace std;

#define NUM_Thread 4

//metodo de impresion de los hilos
void* char_print (void* parametros){
/*se realiza la conversion de los parametros de entrada utilizando apuntadores 
a apuntadores de tipo entero*/
	int tid = *((int*)parametros);
	cout << "Este es el hilo: " << tid << endl;
	pthread_exit(NULL);
}//char_print

void mensaje(){
 	int a = 1000, b = 5007;
 	float c;
 	
 	c = a + b;
 	
 	cout << "La suma es: " << c << endl;

	return NULL;
}

int main(){
	pthread_t threads[NUM_Thread];
	int hilos[NUM_Thread]; //El arreglo que que almacena el valor de i
	int rc, i;
	for (i = 0; i < NUM_Thread; i++){
		cout << "El ID del hilo es: " << i << endl;
		hilos[i] = i; //guardamos el valor de i
		//creamos el hilo para colvertirlo en un puntoreo vacio
		rc = pthread_create(&threads[i], NULL, char_print, (void*)&(hilos[i]));
		if (rc){
			cout << "Escribiendo el hilo" << rc << endl;
			exit(-1);
		}//if
	}//ciclo for
	
	
	
	pthread_exit(NULL);
return 0;
}//main
