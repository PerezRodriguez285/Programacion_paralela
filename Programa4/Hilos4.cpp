#include <thread> //libreria de hilos
#include <iostream>

using namespace std;

void thread_funtion(int x)//funcion de hilos
{
	int aux;
	int suma=0;
	switch(x){
		case 1:
			for(aux=1;aux<=2499;aux++){
				suma+=aux;
			}
			cout<<"Suma: "<<suma<<endl;
			break;
		case 2:
			for(aux=2500;aux<=4999;aux++){
				suma+=aux;
			}
			cout<<"Suma: "<<suma<<endl;
			break;
		case 3:
			for(aux=5000;aux<=7499;aux++){
				suma+=aux;
			}
			cout<<"Suma: "<<suma<<endl;
			break;
		case 4:
			for(aux=7499;aux<=1000;aux++){
				suma+=aux;
			}
			cout<<"Suma: "<<suma<<endl;
			break;
	}
}

int main()
{
	thread t1(&thread_funtion,1);//crear un hilo idHilo(&funcionHilo,parametro)
	thread t2(&thread_funtion,2);
	thread t3(&thread_funtion,3);
	thread t4(&thread_funtion,4);
	
	cout<<"main thread\n"<<this_thread::get_id()<<endl;
	
	t1.join();//Poner en espera el hilo
	t2.join();
	t3.join();
	t4.join();

	return 0;
}
