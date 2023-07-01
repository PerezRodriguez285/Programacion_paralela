/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programacion Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Tema: Programa que crea hilos en c++
Compilacion: g++ -o crear_hilo crea_hilo.cpp -pthread
Ejecucion: /.crear_hilo
*/
#include <iostream>
#include <cstdio>
#include <pthread.h>
using namespace std;
//programa que permite escribir x y 0 de manera aleatoria

//permite imprimir x
void* print_xs (void* unused){
	while(1)
	cout<<"x";
	return NULL;	
}//print_xs

int main(){
	pthread_t th1;
	pthread_create (&th1, NULL, &print_xs, NULL);
	while(1)
	cout<<"o";
	return 0;
	pthread_exit(NULL);
}//main
