/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programacion Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Compilacion: g++ -o ejecutable Programa2.cpp -pthread
Ejecucion: /.ejecutable archivo.txt valor (./ejecutable archivo.txt 3.14)
*/
#include <iostream>
using namespace std;
//programa de lectura de archivos
int main(int argc, char *argv[]){
	//declaramos variables
	int a;
	float x;
	//ingresar un parametro al dato o archivo
	//a=atoi(argv[1]); //atoi convertir valores de alfabetico a entero
	//x=3.142559;
	
	a=atoi(argv[1]); 
	x=atof(argv[2]);
	
	cout<<"El programa se llama ......."<< argv[0]<<endl;
	cout<<"El valor de a es:"<< a<< endl;
	cout<<"Pi es: "<< x << endl;
	return 0;
}//main
