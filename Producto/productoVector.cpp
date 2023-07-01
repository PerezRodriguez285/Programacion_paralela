#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
	int i,j,n,m;
	float V[10], W[10];
	//vector<int> V;
	//vector<int> W;
	float resultado = 0;
	
	cout << "Tamaño del primer vector: ";
	cin >> n;
	cout << "Tamaño del segundo vector: ";
	cin >> m;
	
	if(n != m){
		cout << "Los vectores no son del mismo tamaño";
	}else{
		cout << "Datos del primer vector\n";
		for (i = 0; i < n; i++){
			cin >> V[i];
		}
		cout << "Datos del segundo vector\n";
		for (j = 0; j < m; j++){
			cin >> W[j];
		}
		
	}
	
	for (int l = 0; l < m; l++){
		resultado += V[l]*W[l];
	}
	
	cout<<"El producto dot de 2 vectores es: "<< endl; 
  	cout<< resultado << endl;

}
