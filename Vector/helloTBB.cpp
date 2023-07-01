/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: Hola mundo a traves de TBB
//Compilación: g++ -std=c++17 -o hello helloTBB.cpp -ltbb
Ejecucion: /.hello
*/
#include <iostream>
#include <tbb/tbb.h>

using namespace std;
using namespace tbb;

int main(int argc, char *argv[]){
	tbb::parallel_invoke(
		[](){cout << "Hello desde ";},
		[](){cout << "tbb ";},
		[](){cout << "entre lineas ";}
	);
	return 0;
}
