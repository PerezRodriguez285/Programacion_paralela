#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

typedef struct {
	double *a;
	double *b;
	double sum;
	int esp; //veclen

} DOTDATA;

//variables globales
#define NUM_Threads 4
#define ESP 100000
DOTDATA dotstr;
pthread_t callThd[NUM_Threads];
pthread_mutex_t mutexsum; //creamos un hilo con el parametro mutex

//funcionque hace el producto de 2 vectores
void *dotprod(void *arg){
	int i;
	int inicio, len, fin;
	long offset; //permite indicar el tamaño de la variable
	double mysum = 0;
	double *x, *y;
	offset = (long)arg; 
	
	len = dotstr.esp;
	inicio = offset*len;
	fin = inicio + len;
	x = dotstr.a;
	y = dotstr.b;

	for ( i = inicio; i < fin; i++){
		mysum += (x[i]*y[i]);
	}//for
	
	pthread_mutex_lock (&mutexsum); //hace referencia al parametro mutex en caso de que este bloqueado ademas de indicar si hay error
	dotstr.sum += mysum;
	cout << "Hilos ID:" << mysum << endl;
	
	pthread_mutex_unlock (&mutexsum);
	pthread_exit((void*) 0);
}//dotpord

int main(int argc, char *argv[]){
	long i;
	double *a, *b;
	void *status;
	pthread_attr_t attr;
	
	a = (double*) malloc (NUM_Threads*ESP*sizeof(double));
	b = (double*) malloc (NUM_Threads*ESP*sizeof(double));
	
	for (i = 0; i < ESP*NUM_Threads; i++){
		a[i] = 1;
		b[i] = a[i];
	}
	
	dotstr.esp = ESP;
	dotstr.a = a;
	dotstr.b = b;
	dotstr.sum = 0;
	
	pthread_mutex_init(&mutexsum, NULL);
	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for(i = 0; i < NUM_Threads; i++){
		pthread_create(&callThd[i], &attr, dotprod, (void*)i);
	}
	
	pthread_attr_destroy(&attr); //destruye la variable condicion

	for(i = 0; i < NUM_Threads; i++){
		pthread_join(callThd[i],&status);
	}
	
	cout << "Producto" << dotstr.sum << endl;
	free (a);
	free (b);
	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
	
	return 0;
}
