#include <iostream>
float* crea_vect(int);
int * crea_veci(int);
bool * crea_bool(int);
float* lee_vect(char *, int);
int ini_vecint(int *, int);
int muestra_vect(float*, int);
int muestra_vecint(int *, int );
int muestra_bool(bool * , int);
void productoVector(char *, char *, int, int);
float** crea_mat(int, int);
float** lee_mat(char *, int, int);
void muestra_mat(float**, int,int);
void esc_mat(float **,char *,int, int );
float vecxvec(float*,float*,int);
void matxVec(const float* ,const float* , float* , int, int);
void matrixVectorMult(double*, double*, double*, int, int);
void productoMatxVec(char *, char *, int, int, int);
float ** mat_trans(float **,int, int);
float sigmod(float);
int* salida_int(float *,int);
