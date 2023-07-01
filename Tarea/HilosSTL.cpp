/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Programa que posee 4 hilos a traves de un arreglo usando stl*/
#include <iostream>
#include <pthread.h>
#include <cstdio>
using namespace std;

#define NUM_Threads 4

struct char_print_parms{
	int count;
	char *character;
}; //char_print_parmms

void* char_print (void* parameters){
	struct char_print_parms *my_data;
	my_data = (struct char_print_parms*) parameters;
	
	cout << "ID del hilo: "<< my_data->count << endl;
	cout << "Mensaje: " << my_data->character << endl;

	pthread_exit(NULL);
}//void char_print

int main(){
	pthread_t threads[NUM_Threads];
	struct char_print_parms td[NUM_Threads];
	int rc, i;
	for(i = 0; i < NUM_Threads; i++){
		cout << "Creando hilos: " << i << endl;
		td[i].count = i;
		td[i].character = "Este es el mensaje";
		rc = pthread_create(&threads[i], NULL, char_print, (void*)&td[i]);
		if (rc){
         		cout << "Error:unable to create thread," << rc << endl;
         		exit(-1);
      		}
	}//for
	pthread_exit(NULL);
	return 0;
}//main
