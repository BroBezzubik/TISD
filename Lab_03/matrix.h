#ifndef MATRIX_H
#define MATRIX_H

#define N 3

struct ElementNode {
    int index;
    struct ElementNode *next;
};

struct SparseMatrix {
    int *A;
    int *IA;
    struct ElementNode *JA;
    int size; // for A and IA
    int rows;
    int columns;
};

void addNode(SparseMatrix *m, ElementNode *node);
int getElemet(SparseMatrix *m, int i, int j);
SparseMatrix* generateRandomMatrix(int rows, int colums);
void printMatrixDetails(SparseMatrix *m);
void printMatrix(SparseMatrix *m);
double sumOfMatrixStandart(SparseMatrix *m1,SparseMatrix *m2, int rows, int columns);
SparseMatrix *sumOfMatrix(SparseMatrix *m1,SparseMatrix *m2, int rows, int columns, unsigned sum);
struct SparseMatrix *manual(int rows, int columns);

#endif // MATRIX_H
