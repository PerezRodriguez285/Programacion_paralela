#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include <cmath>

using namespace std;
float** crea_mat(int, int);
float** lee_mat(char *, int, int);
void muestra_mat(float**, int,int);
void distancia(float**,float**,int,int,int,int);
void centroides (float**,float**,int,int );
void escritura(float**);