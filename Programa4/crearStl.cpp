/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: programa que usa hilos usando la libreria thread (variacion del programa anterior)
*/
#include <iostream>
#include <thread>
using namespace std;
//usamos la clase thread de STL
void thread_function(int x){
	cout << "Funciones de hilos\n"<< x << endl;
	cout << "thread id:"<<this_thread::get_id()<<endl;
	cout << "Number of thread hrdw"<<thread::hardware_concurrency()<<endl;
} // thread

int main(){
//creamos los objetos que tiene el tipo de thread
	thread t1(&thread_function,1);
	thread t2(&thread_function,2);
	thread t3(&thread_function,3);
	cout << "main thread\n"<<this_thread::get_id()<<endl;
	t1.join();
	t2.join();
	t3.join();
	return 0;
}//main
