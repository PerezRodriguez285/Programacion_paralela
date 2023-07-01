#include<pthread.h>
#include<cstdio>
#include<iostream>

using namespace std;
struct estru1{
	FILE *archivo1;
    	FILE *archivo2;
	int up;
    	int down;
};

int sumas = 0;
float m1[10000];
float m2[10000];

void* producto(void* str){
	struct estru1* p=(struct estru1*)str;
	int aux = 0;
	int suma=0;
	for (int i = p->down; i < p->up; i++)
	{
		//aux = m1[i] * m2[i];
		//suma = suma + aux; 
		suma += m1[i] * m2[i];
	}
	sumas = sumas + suma;
}

void* leer_archivos(void* parametros){

	struct estru1* p = (struct estru1*) parametros;
	string filename=p->archivo1;
    	ifstream archivo(filename); 
    	if (!archivo.is_open()) { 
    		 string numeros;
    		 getline(archivo, numeros);
        cout << "No se pudo abrir el archivo" << endl;
        
    	}///if
   	string linea;
    	while (getline(archivo, linea)) { 
        	cout <<" "<< linea << endl;
   	 }

    	archivo.close(); 
  
	return NULL;

}	

void* leerVec (void* arg){
    float cont = 1;
    struct estru1* q = (struct estru1*)arg;
    rewind(q->archivo1);
    int i = 0;
    int j = 0;
    while (feof(q->archivo1) == 0)
    {
        fscanf(q->archivo1,"%f",&cont);
        m1[i] = cont;
        i++;
        
    }
    
    struct estru1* p = (struct estru1*)arg;
    rewind(p->archivo1);
    
    while (feof(p->archivo2) == 0)
    {
        fscanf(p->archivo2,"%f",&cont);
        m2[i] = cont;
        i++;
        
    }
}

int main(int argc, char const *argv[]){
    	int sum0,sum1,sum2,sum3;
   	sum0=sum1=sum2=sum3=1;
	pthread_t t[4];
	estru1 st[4];
	st[0].archivo1 = fopen("vector1.txt","r");
    	st[0].archivo2 = fopen("vector2.txt","r");
	st[0].up=250;
	st[0].down=0;
	for (int i = 1; i <= 4; i++){
		st[i].up = st[i-1].up + 2500;
		st[i].down = st[i-1].down + 2500;
	}

    	for (int i = 0; i < 10000; i++){
        m1[i] = 1;
        m2[i] = 1; 
   	}

	pthread_create(&t[0],NULL,&producto,&st[0]);
	pthread_create(&t[1],NULL,&producto,&st[1]);
   	pthread_create(&t[2],NULL,&producto,&st[2]);
	pthread_create(&t[3],NULL,&producto,&st[3]);
	pthread_join(t[0],(void**) &sum0);
	pthread_join(t[1],(void**) &sum1);
    	pthread_join(t[2],(void**) &sum2);
    	pthread_join(t[3],(void**) &sum3);

	int sumatotal=sum0+sum1+sum2+sum3;
    	cout<<"\nEl producto de 2 vectores es: "<<sumatotal<<endl;
	pthread_exit(NULL);
}

