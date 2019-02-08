#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, const char * argv[]) {
    setbuf(stdout,NULL);
    int ch = 3;
    while (ch != 0)
    {
        printf("Summ of matrix (random-1/manual-2/exit-0)\n");
        scanf("%d", &ch);
        if (ch == 1)
        {
            printf("Input matrix size\n");
            int columns = 0, rows = 0;
            scanf("%d", &columns);
            scanf("%d", &rows);
            struct SparseMatrix *m1 = generateRandomMatrix(rows, columns);
            struct SparseMatrix *m2 = generateRandomMatrix(rows, columns);
            if (rows*columns < 100)
            {
                printf("Generating matrix: \n");
                printMatrix(m1);
                printf("\n");
                printMatrix(m2);
                printf("\n");
            }
            else
            {
                if (rows*columns<1000)
                {
                    printf("Generating matrix: \n");
                    printMatrixDetails(m1);
                    printMatrixDetails(m2);
                }
            }
            unsigned sum = sumOfMatrixStandart(m1, m2, rows, columns);
            sumOfMatrix(m1, m2, rows, columns, sum);
            free(m1);
            free(m2);
        }
        else if (ch == 2)
        {
            printf("Input matrix size\n");
            int columns = 0, rows = 0;
            scanf("%d", &columns);
            scanf("%d", &rows);
            struct SparseMatrix *m1 = manual(rows, columns);
            struct SparseMatrix *m2 = manual(rows, columns);
            if (rows*columns < 400)
            {
                printf("Matrix: \n");
                printMatrix(m1);
                printf("\n");
                printMatrix(m2);
                printf("\n");
            }
            else
            {
                printMatrixDetails(m1);
                printMatrixDetails(m2);
            }
            unsigned sum = sumOfMatrixStandart(m1, m2, rows, columns);
            struct SparseMatrix *res = sumOfMatrix(m1, m2, rows, columns, sum);
            printMatrixDetails(res);
        }
    }

    return 0;
}
