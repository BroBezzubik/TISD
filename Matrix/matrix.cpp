#include "matrix.h"

void Matrix::setArray(dischargedArray &array, int n){
    array.j = 1;
    array.n = n + 1;
    array.AN = new double[n + 1];
    array.JA = new int[n + 1];
    array.IP = new int[n + 1];

    std::memset(array.AN, 0, sizeof(double));
    std::memset(array.JA, 0, sizeof(double));
    std::memset(array.IP, 0, sizeof(double));

}

void Matrix::setMatrix(Matrix::dischargedMatrix &matrix){
    matrix.arrays = NULL;
    matrix.m = 0;
    matrix.n = 0;
}

void Matrix::fillArray(dischargedArray &array){
    for (int i = 1; i < array.n; i++){
        std::cout << ">> ";
        std::cin >> array.AN[i];
    }
    updateArrayData(array);
}

void Matrix::fillMatrix(dischargedMatrix &matrix, int n){
    std::cout << "Input colums: ";
    std::cin >> matrix.n;
    std::cout << "Input rows: ";
    std::cin >> matrix.m;

    matrix.arrays = new dischargedArray[matrix.m];
    for (int i = 0; i < matrix.m; i++){
        setArray(matrix.arrays[i], matrix.n);
        fillArray(matrix.arrays[i]);
    }
}

void Matrix::updateArrayData(dischargedArray &array){
    int j = 1;
    for (int i = 1; i < array.n; i++){
        if (array.AN[i] != 0){
            array.JA[j] = i;
            j++;
        }
    }
    array.j = j;

    for (int i = 1; i < j; i++){
        array.IP[array.JA[i]] = i;
    }
}

double Matrix::multiplyArray(dischargedArray &array1, dischargedArray &array2){
    double sum = 0;
    for (int i = 1; i <= array2.j; i++){
        int jb = array2.JA[i];
        if (array1.IP[jb] != 0){
            sum += array1.AN[jb] * array2.AN[jb];
        }
    }

    std::cout << sum << std::endl;
}

Matrix::dischargedMatrix* Matrix::sumMatrix(dischargedMatrix &matrix1, dischargedMatrix &matrix2){
    if (matrix1.n == matrix2.n && matrix1.m == matrix2.m){
        dischargedMatrix *matrix3 = new dischargedMatrix;
        matrix3->arrays = new dischargedArray[matrix1.m];
        matrix3->m = matrix1.m;
        matrix3->n = matrix1.n;
        for (int i = 0; i < matrix1.m; i++){
            setArray(matrix3->arrays[i], matrix1.n);
        }
        for (int i = 0; i < matrix1.m; i++){
            for (int j = 1; j <= matrix2.arrays[i].j; j++){
                int jb = matrix1.arrays[i].JA[j];
                double sum = matrix1.arrays[i].AN[jb] + matrix2.arrays[i].AN[jb];
                matrix3->arrays[i].AN[jb] = sum;
            }

            for (int j = 1; j <= matrix1.arrays[i].j; j++){
                int jb = matrix2.arrays[i].JA[j];
                double sum = matrix1.arrays[i].AN[jb] + matrix2.arrays[i].AN[jb];
                matrix3->arrays[i].AN[jb] = sum;
            }
            updateArrayData(matrix3->arrays[i]);
        }
        return matrix3;
    }
}

