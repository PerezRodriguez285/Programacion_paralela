#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double sum;

int main(int argc, char *argv[]){
	double A[256]; 
	double B[256];
	int i;
	int n=256;
	for (i = 0; i < n; i++){
		A[i] = i*0.5;
		B[i]= i*2.0;
	}
	sum = 0;

	#pragma omp parallel for reduction(+:sum)
	for (i = 0; i < n; i++){
		sum = sum+A[i]*B[i];
	}
	printf("sum= \%f ",sum);
	
	return 0;
}//
