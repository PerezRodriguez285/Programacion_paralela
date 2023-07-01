#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <thread>

using namespace std;
//mandamos una funcion que lea un vector desde el principio
void *ifstream_lines(ifstream& fs, vector<int> X, const &vec){
	vector<int> out;
	int temp, i;
	
	while(fs >> temp){ //
		out.push_back(temp); //imprime los valores de forma aleatoria del archivo que tiene el vector
		copy(X,out);
	}
	return out;
}


int main(int argc, char *argv[]){
	vector<int> V;
	ifstream fs(argv[1]);
	//V=ifstream_lines(fs);
	int i;
	thread th=(&ifstream_lines,argv[1],V,23);
	
	for(i = 0; i<V.size();++i){
		cout<<V[i]<<","<<endl; //se muestran los datos del vector
	}
	
	//pthread_create(&hilo1_id, NULL, , NULL);
	
	//pthread_join (hilo1_id, NULL);
	//pthread_exit(NULL);
	th.join();
	
	return 0;
}
