#include<pthread.h>
#include<cstdio>
#include<iostream>
//g++ -o out.x MatrizxVector.cpp -lpthread
using namespace std;
struct Str
{
    FILE *archivoMat;
    FILE *archivoVec;
    int Inicio;
    int Final;
};

float suma[1000];
int tam = 1000;
float **Matriz = new float*[tam];
float *vector = new float[tam];

void* sumar(void* str)
{
	struct Str* p=(struct Str*)str;
	int aux = 0;
	int sumas=0;
	for (int i = p->Inicio; i < p->Final; i++)
	{
        for (int j = 0; j < tam; j++)
        {
            suma[i] += Matriz[i][j] * vector[j];
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
}


void* leerVec (void* arg)
{
    float cont = 1;
    struct Str* q = (struct Str*)arg;
    rewind(q->archivoVec);
    int i = 0;
    int j = 0;
    while (feof(q->archivoVec) == 0)
    {
        fscanf(q->archivoVec,"%f",&cont);
        vector[i] = cont;
        i++;
        
    }
}

int main()
{   
    Str fe[4];
	pthread_t t[4];
    fe[0].archivoMat = fopen("matriz.txt","r");
    fe[0].archivoVec = fopen("vector2.txt","r");
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
    }

    for(int i = 0; i <= tam; i++)
    {   
        Matriz[i] = new float[tam];
    }
    leerMat(&fe[0]);
    leerVec(&fe[0]);

	pthread_create(&t[0],NULL,&sumar,&fe[0]);
	pthread_create(&t[1],NULL,&sumar,&fe[1]);
    pthread_create(&t[2],NULL,&sumar,&fe[2]);
	pthread_create(&t[3],NULL,&sumar,&fe[3]);
	pthread_join(t[0],(void**) NULL);
	pthread_join(t[1],(void**) NULL);
    pthread_join(t[2],(void**) NULL);
    pthread_join(t[3],(void**) NULL);

    for (int i = 0; i < tam; i++)
    {
        cout<<"["<< i <<"]: "<<suma[i]<<endl;
	}
	pthread_exit(NULL);
}
