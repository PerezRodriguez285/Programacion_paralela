#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <pthread.h>
#include <string>
#include <thread>

using namespace std;

struct vec{
	string ruta = "vector.txt";
};

vector<int> vectores;

void* leer_archivos(void* parametros){

	struct vec* p = (struct vec*) parametros;
	string filename=p->ruta;
    	ifstream archivo(filename); 
    	if (!archivo.is_open()) { // Verifica que el archivo se haya abierto 
    		 string numeros;
    		 getline(archivo, numeros); // Leemos la primera línea del archivo
        cout << "No se pudo abrir el archivo" << endl;
        
    	}///if
   	string linea;
    	while (getline(archivo, linea)) { // Lee cada línea del archivo
    		//int num = stoi(numeros); // Convertimos la cadena a entero
    		//vectores.push_back(num);
        	cout <<" "<< linea << endl;
   	 }

    	archivo.close(); // Cierra el archivo
  
	return NULL;

}	

int main(int argc, char *argv[]){
	int rn,i,x,y,it;
	rn = atoi(argv[3]);
	vector<int> V;
	//f1.open(argv[1],ios::in);
	
	//thread t1(&leer_archivos, V,5); // eltamaño del archivo

	pthread_t hilo2_id;
	struct vec hilos_arg;

	pthread_create(&hilo2_id, NULL, leer_archivos, &hilos_arg);
	pthread_join (hilo2_id, NULL);
	pthread_exit(NULL);
	return 0;
}
