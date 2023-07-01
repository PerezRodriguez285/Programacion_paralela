#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <pthread.h>

using namespace std;

int main(int argc, char *argv[]){
	//declaracion de variables
	int resultado = 0;
	int i, j, rn, x, y, tamano;
	rn = atoi(argv[3]);
	fstream f1,f2;
	vector<int> V;
	vector<int> W;
	
	f1.open(argv[1],ios::in);
	f2.open(argv[2],ios::in);
	
	for(i = 0; i < rn; i++){
		f1 >> x; //lee la x y la agrega a la ultima posicion del arreglo
		V.push_back(x);
	}
	
	for(i = 0; i < rn; i++){
		f2 >> y;	
		W.push_back(y);	
	}
	
	
	for (j = 0; j < V.size(); j++){
		resultado += V[j]*W[j];
	}
	
	cout<<"El producto dot de 2 vectores es: "<< endl; 
  	cout<< resultado << endl;
	
	return 0;
}
