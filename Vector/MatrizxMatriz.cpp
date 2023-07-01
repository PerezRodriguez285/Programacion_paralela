#include<pthread.h>
#include<cstdio>
#include<iostream>
//g++ -o out.x MatrizxMatriz.cpp -lpthread
using namespace std;
struct Str
{
    FILE *archivoMat;
    FILE *archivoMat2;
    int Inicio;
    int Final;
};

float Resultado[1000][1000];
int tam = 1000;
float **Matriz = new float*[tam];
float **Matriz2 = new float*[tam];

void* Operacion(void* str)
{
	struct Str* p=(struct Str*)str;
	int sumas = 0;
    for (int i = p->Inicio; i < p->Final; i++)
	{
        for (int j = 0; j < tam; j++)
	        {
	        Resultado[i][j] = 0;
            for (int k = 0; k < tam ; k++)
            {
                Resultado[i][j] += (Matriz[i][k] * Matriz2[k][j]);
            }
        }
    }
	return NULL;
}

void* leerMat (void* arg)
{
	float cont = 1;
    struct Str* q = (struct Str*)arg;
    rewind(q->archivoMat);
    int i = 0;
    int j = 0;
    cout<<"Leeiendo Matriz 1 ..."<<endl;
    while (feof(q->archivoMat) == 0)
    {
        if(i == 1000)
        {   
            j++;
            i = 0;
        }
        fscanf(q->archivoMat,"%f",&cont);
        Matriz[i][j] = cont;
        i++;
    }
    i = 0;
    j = 0;
    cont = 1;
    cout<<"Leeiendo Matriz 2 ..."<<endl;
    while (feof(q->archivoMat2) == 0)
    {
        if(i == 1000)
        {   
            j++;
            i = 0;
        }
        fscanf(q->archivoMat2,"%f",&cont);
        Matriz2[i][j] = cont;
        i++;
    }
    
}

int main()
{   
    Str fe[4];
	pthread_t t[4];
    fe[0].archivoMat = fopen("hola.txt","r");
    fe[0].archivoMat2 = fopen("hola.txt","r");
    fe[0].Inicio = 0;
    fe[0].Final = 250;
    for (int i = 1; i < 4; i++)
    {
        fe[i].Inicio = fe[i-1].Inicio + 250;
        fe[i].Final = fe[i-1].Final + 250;
    }

    for(int i = 0; i <= tam; i++)
    {   
        Matriz[i] = new float[tam];
        Matriz2[i] = new float[tam];
    }

    leerMat(&fe[0]);
	
	cout<<"Calculando operaciones ..."<<endl;
	pthread_create(&t[0],NULL,&Operacion,&fe[0]);
	pthread_create(&t[1],NULL,&Operacion,&fe[1]);
    pthread_create(&t[2],NULL,&Operacion,&fe[2]);
	pthread_create(&t[3],NULL,&Operacion,&fe[3]);
	pthread_join(t[0],(void**) NULL);
	pthread_join(t[1],(void**) NULL);
    pthread_join(t[2],(void**) NULL);
    pthread_join(t[3],(void**) NULL);

    for (int i = 0; i < tam; i+=100)
    {
        for (int j = 0; j < tam; j+=100)    
        {
           cout<<"["<< i <<","<< j <<"]:\t"<< Resultado[i][j]<<endl;
	    }
	}
	cout<<"["<< 999 <<","<< 999 <<"]:\t"<< Resultado[999][999]<<endl;
    pthread_exit(NULL);
    
}
