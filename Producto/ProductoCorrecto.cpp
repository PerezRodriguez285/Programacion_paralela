#include<iostream>
#include<pthread.h>
#include<cstdio>

using namespace std;

struct archivo{
	FILE *archivoMat;
    	FILE *archivoVec;
	int Inicio, Final;
};

float suma = 0;
int tam = 1000;
float *Matriz = new float[tam];
float *vector = new float[tam];

void *producto(void* parametro){
	struct archivo* p=(struct archivo*)parametro;
	int aux = 0;
	int sumas=0;
	for (int i = p->Inicio; i < p->Final; i++){
        	for (int j = 0; j < tam; j++){
            		suma += Matriz[j]*vector[j];
     	   } 
	}
	return NULL;

}

void* leerMat (void* arg){
    float cont = 1;
    struct archivo* q = (struct archivo*)arg;
    rewind(q->archivoMat);
    int i = 0;
    int j = 0;
    while (feof(q->archivoMat) == 0)
    {
        fscanf(q->archivoMat,"%f",&cont);
        vector[i] = cont;
        i++;
        
    }
}

void* leerVec (void* arg){
    float cont = 1;
    struct archivo* q = (struct archivo*)arg;
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

int main(int argc, char const *argv[]){
	archivo fe[4];
	pthread_t t[4];
    fe[0].archivoMat = fopen("vector1.txt","r");
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
        Matriz[i];
    }
    leerMat(&fe[0]);
    leerVec(&fe[0]);

	pthread_create(&t[0],NULL,&producto,&fe[0]);
	pthread_create(&t[1],NULL,&producto,&fe[1]);
    	pthread_create(&t[2],NULL,producto,&fe[2]);
	pthread_create(&t[3],NULL,&producto,&fe[3]);
	pthread_join(t[0],(void**) NULL);
	pthread_join(t[1],(void**) NULL);
    pthread_join(t[2],(void**) NULL);
    pthread_join(t[3],(void**) NULL);

    for (int i = 0; i < tam; i++)
    {
        cout<<"["<< i <<"]: "<<suma<<endl;
	}
	pthread_exit(NULL);


	return 0;
}


