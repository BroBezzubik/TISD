#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<cstdlib>
#include <cstring>

namespace Matrix{
    struct dischargedArray;
    struct dischargedMatrix;
    void setMatrix(dischargedMatrix &matrix);
    void setArray(dischargedArray &array, int n);
    void fillMatrix(dischargedMatrix &matrix, int n);
    void fillArray(dischargedArray &array);
    void updateArrayData(dischargedArray &array);
    double multiplyArray(dischargedArray &array1, dischargedArray &array2);
    dischargedMatrix* sumMatrix(dischargedMatrix &matrix1, dischargedMatrix &matrix2);

}

struct Matrix::dischargedArray{
    int n;
    int j;
    double *array;
    int *JA;
    double *AN;
    int *IP;
};

struct Matrix::dischargedMatrix{
    dischargedArray *arrays;
    int n;
    int m;
};


#endif // MATRIX_H
