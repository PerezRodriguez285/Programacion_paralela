#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include <cmath>
#include "func_omp.h"
using namespace std;

int fin=0;
float **M;
float identificadorC[5]= {0,1,2,3,4};
float *identificadorO=new float[100];


float** crea_mat(int r, int c){
	float **X;
	X = new float *[r];
	
	for(int i = 0; i < r; i++){

		X[i]=new float[c];

	}//for
	
	//cout<<"Se asignó memoria a la matriz..."<<endl;
	return X;
}

float** lee_mat(char *nom_arch, int r, int c){
	float **Y;
	Y = crea_mat(r,c);
	

	fstream f1;
	f1.open(nom_arch, ios::in);

	while(!f1.eof()){

		for(int i = 0; i < r; i++){

			for(int j = 0;j < c; j++){

			f1>>Y[i][j];
			
			}//for

		}//for

	}//while

	f1.close();
	//cout<<"Matriz leida"<<endl;
	return Y;
}

void muestra_mat(float **M, int m, int n){
	int i,j;
	
	for(i=0; i < m; i++){
		for(j = 0; j < n; j++){
			cout << M[i][j] << ",";
		}
		cout << endl;
	}

}

void distancia(float **M,float **N,int numObjetos,int numCentroides,int fila,int columna){
    double centroide = 0.0, puntoActual = 0.0;
    do{
        #pragma omp for private(i) 
        for(int i=0;i<numObjetos;i++){
           	centroide = sqrt(pow(N[0][i]-M[0][0],2)+pow(N[1][i]-M[1][0],2));
            identificadorO[i]=identificadorC[0];
            for(int j=1;j<numCentroides;j++){
                puntoActual =sqrt(pow(N[0][i]-M[0][j],2)+pow(N[1][i]-M[1][j],2));
                if(centroide>=puntoActual){

                    identificadorO[i]=identificadorC[j];
                    
                }          
            }  
        }   
    fin++;
    centroides(M,N,numObjetos,numCentroides);	
   	}while(fin<=8);
 	 escritura(M);
}


void centroides (float **M,float **N,int numObjetos,int numCentroides)  {
    float sumaTotal=0,totalX=0,totalY=0;
    #pragma omp parallel for collapse(2) schedule(dynamic) 
    for(int i=0;i<numCentroides;i++){
        for(int j=0;j<numObjetos;j++){
            if(identificadorC[i]==identificadorO[j]){
                totalX += N[0][j];
                totalY += N[1][j];
                sumaTotal ++;  
            }
        }
    	if(sumaTotal !=0){
    		totalX=(totalX/sumaTotal);
    		totalY=(totalY/sumaTotal);
    		M[0][i]=totalX;
    		M[1][i]=totalY;
    	}
            
        	totalX=0;
            totalY=0;
            sumaTotal=0;        
    }
         
}


void escritura(float **M){
		string nombreArchivo = "resultados.txt";
    	ofstream archivo;
		archivo.open(nombreArchivo.c_str(), fstream::out);
		archivo<<" "<<endl;
		archivo << "10.41589 7.23901"<<endl;
		for (int i=0;i<5;i++){
			if(M[0][i]!=0){
			archivo<<M[0][i]<<" "<<M[1][i]<<endl;}
		}
	
    // Finalmente lo cerramos
		archivo.close();

}
