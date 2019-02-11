#include <iostream>
#include "matrix.h"

using namespace std;

int main(){
    Matrix::dischargedMatrix matrix1;
    Matrix::dischargedMatrix matrix2;
    Matrix::dischargedMatrix *matrix3;

    Matrix::setMatrix(matrix1);
    Matrix::setMatrix(matrix2);

    Matrix::fillMatrix(matrix1, 0);
    Matrix::fillMatrix(matrix2, 0);
    matrix3 = Matrix::sumMatrix(matrix1, matrix2);

    std::cout << matrix3->n << " " << matrix3->m << std::endl;

    for (int i = 0; i < matrix3->m; i++){
        std::cout << i << ")" << std::endl;
        std::cout << "Array AN: ";
        for (int j = 1; j < matrix3->n + 1; j++){
            std::cout << matrix3->arrays[i].AN[j] << ' ';
        }
        std::cout << "Array JA: ";
        for (int j = 1; j < matrix3->arrays[i].j; j++)
        {
            std::cout << matrix3->arrays[i].JA[j] << ' ';
        }
        std::cout << "Array IA: ";
        for (int j = 1; j < matrix3->n + 1; j++){
            std::cout << matrix3->arrays[i].IP[j] << ' ';
        }
        std::cout << std::endl;
    }
}
