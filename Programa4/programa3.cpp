#include <iostream>
#include <thread>

using namespace std;

int NumHilos = 4; //numero de hilos
int Rango = 10000 / NumHilos; //distribuye equitatativamente el rango

int sum;

//Funcion para los hilos que hacen la suma
void sumas(int start, int end) {
    int local_sum = 0;
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }
    sum += local_sum;
}//suma

int main() {
    // Iniciar cuatro hilos que suman partes de la secuencia
    thread threads[NumHilos]; //Crea un arreglo de hilos
    for (int i = 0; i < NumHilos; i++) {

        //Calculo de el rango de los valores para cada hilo
        int start = i * Rango + 1; 
        int end = (i + 1) * Rango; 

        threads[i] = thread(sumas, start, end); //se pasan los datos a los hilos (funcion, inicio, fin)

    }

    for (int i = 0; i < NumHilos; i++) {
        threads[i].join();
    }
    // Imprimir la suma total
  cout << "La suma de 1 a 10000 es: " << sum <<endl;

    return 0;
}
