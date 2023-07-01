/*
UNIVERSIDAD AUTONOMA DEL ESTADO DE MÉXICO
CU UAEM ZUMPANGO
UA: Programación Paralela
Profesor: Mtro. Manuel Almeida Vazquez
Nombre: Antonio Alberto de la Luz Pérez Rodriguez
Actividad: suma de los valores de 1 hasta 10,000 a través de hilos
*/
#include <iostream>
#include <thread>

using namespace std;

const int NumHilos = 4; //numero de hilos
const int Rango = 10000 / NumHilos; //distribuye equitatativamente el rango

int sum; //variable que almacena la suma

//Funcion para los hilos que hacen la suma

void sumRango(int start, int end) {
    int local_sum = 0;
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }
    sum += local_sum;
}

int main() {
    // Iniciar cuatro hilos que suman partes de la secuencia
    thread threads[NumHilos]; //Crea un arreglo de hilos
    for (int i = 0; i < NumHilos; i++) {
        //Calculo de el rango de los valores para cada hilo
        int start = i * Rango + 1; //da el valor de inicio
        int end = (i + 1) * Rango; //da el valor del final

        threads[i] = thread(sumRango, start, end); //se pasan los datos a los hilos (funcion, inicio, fin)
    }
    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NumHilos; i++) {
        threads[i].join();
    }

    // Imprimir la suma total
    cout << "La suma de 1 a 10000 es: " << sum <<endl;

    return 0;
}
