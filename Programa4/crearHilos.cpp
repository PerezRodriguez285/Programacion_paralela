/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programacion Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: programa que se encarga de crear y ejecutar 3 hilos*/
#include <iostream>
#include <pthread.h>
#include <cstdio>

using namespace std;
//estructura de datos a la funcion
struct char_print_parms{
	char character; //imprimimos el caracter
	int count; //imprimimos enteros
};//struct char

/* SE imprimen los numeros y caracteres a traves de diferentes parametros
utilizando un apuntador la estructura char_print_parms*/
void* char_print (void* parameters){
//hacemos un casting en el que indicamos el parametro en este caso la estructura y lo 
//mandamos al parametro p por medio de apuntadores
	struct char_print_parms* p=(struct char_print_parms*) parameters;
	int i;
	for (i = 0; i < p ->count; ++i) //numero de veces que va a imprimir un caracter
	cout<<p->character;//se imprimen los caracteres
	return NULL;
}//void

int main(){
//declaramos 3 hilos
pthread_t thread1_id;
pthread_t thread2_id;
pthread_t thread3_id;

//declaramos los tipos de estructuras de datos
struct char_print_parms thread1_args;
struct char_print_parms thread2_args;
struct char_print_parms thread3_args;

//creamos los datos del nuevo hilo
thread1_args.character = 'x';
thread1_args.count = 15000;
/*El & indica la direccion de memoria, es decir donde esta guardada la estructura */
pthread_create (&thread1_id, NULL, &char_print, &thread1_args);

thread2_args.character = 'o';
thread2_args.count = 12000;
pthread_create (&thread2_id, NULL, &char_print, &thread2_args);

thread3_args.character = 'y';
thread3_args.count = 10000;
pthread_create (&thread3_id, NULL, &char_print, &thread3_args);

/*pthread join permite que todos los hilos se ejecuten antes que el hilo principal 
y se termine el programa abruptamente antes de que se termine la funcion del programa*/
pthread_join (thread1_id, NULL);
pthread_join (thread2_id, NULL);
pthread_join (thread3_id, NULL);

pthread_exit(NULL);
return 0;
}//main
