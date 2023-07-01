#include <iostream>
#include <fstream>
#include <omp.h>

double* readMatrix(const std::string& filename, int& rows, int& cols) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file \"" << filename << "\".\n";
        return nullptr;
    }
    file >> rows >> cols;
    double* A = new double[rows * cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> A[i * cols + j];
        }
    }
    file.close();
    return A;
}

double* readVector(const std::string& filename, int& size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file \"" << filename << "\".\n";
        return nullptr;
    }
    file >> size;
    double* v = new double[size];
    for (int i = 0; i < size; ++i) {
        file >> v[i];
    }
    file.close();
    return v;
}

void matrixVectorMult(const double* A, const double* x, double* y, int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        double sum = 0;
        for (int j = 0; j < cols; ++j) {
            sum += A[i * cols + j] * x[j];
        }
        y[i] = sum;
    }
}

void printVector(const double* v, int size) {
    std::cout << "Result: [";
    for (int i = 0; i < size; ++i) {
        std::cout << v[i];
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

int main() {
    int rows, cols, size;
    double* A = readMatrix("matriz.txt", rows, cols);
    double* x = readVector("vector2.txt", size);
    double* y = new double[rows];
    matrixVectorMult(A, x, y, rows, cols);
    printVector(y, rows);
    delete[] A;
    delete[] x;
    delete[] y;
    return 0;
}
