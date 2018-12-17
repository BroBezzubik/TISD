#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void addNode(SparseMatrix *m,ElementNode *node) {
    if (m->JA == NULL) {
        m->JA = node;
    } else {
        struct ElementNode *n = m->JA;
        while (n->next) {
            n = n->next;
        }

        n->next = node;
    }
}

int getElemet(SparseMatrix *m, int i, int j) {
    struct ElementNode *jNode = m->JA;

    for (int k = 0; k < j; k++) {
        jNode = jNode->next;
    }

    if (jNode->index < 0) {
        return 0;
    }

    int startIndex = jNode->index;

    int stopIndex = m->size;

    if (jNode->next != NULL) {
        struct ElementNode *n = jNode->next;
        while ((n->index == -1) && (n->next != NULL)) {
            n = n->next;
        }
        if (n->index >= 0) {
            stopIndex = n->index;
        }
    }


    for (int a = startIndex; a < stopIndex; a++) {
        if (m->IA[a] == i) {
            return m->A[a];
        }
    }

    return 0;
}

struct SparseMatrix *generateRandomMatrix(int rows, int columns) {
    struct SparseMatrix *matrix = malloc(sizeof(struct SparseMatrix));

    matrix->A = malloc(columns * rows * sizeof(int));
    matrix->IA = malloc(columns * rows * sizeof(int));
    matrix->JA = NULL;

    matrix->columns = columns;
    matrix->rows = rows;

    int index = 0;

    int pr = 0;
    printf("Input percent of matrix (0 - 100):");
    scanf("%d", &pr);

    int count = 0;

    for (int j = 0; j < columns; j++) {
        // create node for column j
        struct ElementNode *jNode = malloc(sizeof(struct ElementNode));
        jNode->index = -1;
        jNode->next = NULL;

        //printf("%d", (int)rows*columns*pr/100);
        for (int i = 0; i < rows; i++) {
            if ((rand()%100 < (pr)) && (count < (int)rows*columns*pr/100)) {
                int element = rand()%9 + 1;
                //printf("%d, %d\n", (int)rows*columns*pr/100, count);
                if (jNode->index < 0) {
                    jNode->index = index;
                }

                matrix->A[index] = element;
                matrix->IA[index] = i;

                // increase index
                index++;
                count++;
                //printf("%d ", element);
            } else {
                //printf("0 ");
            }
        }

        addNode(matrix, jNode);
        //printf("\n");
    }

    matrix->size = index;

    // shrink matrix
    matrix->A = realloc(matrix->A, index * sizeof(int));
    matrix->IA = realloc(matrix->IA, index * sizeof(int));

    return matrix;
}

void printMatrixDetails(SparseMatrix *m) {
    printf("A, IA, JA:\n\n");

    printf("A: ");
    for (int i = 0; i < m->size; i++) {
        printf("%d ", m->A[i]);
    }

    printf("\n\nIA: ");
    for (int i = 0; i < m->size; i++) {
        printf("%d ", m->IA[i]);
    }

    printf("\n\nJA: ");

    struct ElementNode *n = m->JA;

    while (n) {
        if (n->index != -1)
            printf("%d ", n->index);
        n = n->next;
    }

    printf("\n\n");
}

void printMatrix(SparseMatrix *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            printf("%5d", getElemet(m, i, j));
        }
        printf("\n");
    }
}

double sumOfMatrixStandart(SparseMatrix *m1,SparseMatrix *m2, int rows, int columns)
{
    int matrix[rows][columns];
    int matrix1[rows][columns];
    int matrix2[rows][columns];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix1[i][j] = getElemet(m1, i, j);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix2[i][j] = getElemet(m2, i, j);

    unsigned long tb1, te1;
    tb1 = tick();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i][j] = matrix1[i][j] + matrix2[i][j];

    te1 = tick();
    if (rows*columns<400)
    {
        printf("Summ of matrix: \n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
                printf("%5d", matrix[i][j]);
            printf("\n");
        }
    }
    return (te1 - tb1) / N;
}

struct SparseMatrix *sumOfMatrix(SparseMatrix *m1,SparseMatrix *m2, int rows, int columns, unsigned sum)
{
    int matrix[rows][columns];

    int elements = 0;
    int count = 0;

    int matrix1[rows][columns];
    int matrix2[rows][columns];
    int mj1[m1->size];
    int mj2[m2->size];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i][j] = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            matrix1[i][j] = getElemet(m1, i, j);
            if (matrix1[i][j] != 0)
            {
                mj1[count] = j;
                //printf("%d", j);
                count++;
            }
        }
    count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            matrix2[i][j] = getElemet(m2, i, j);
            if (matrix2[i][j] != 0)
            {
                mj2[count] = j;
                count++;
            }
        }
    count = 0;

    unsigned long tb1, te1;
    tb1 = tick();

    for (int i = 0; i < m1->size; i++)
    {
        int k = mj1[elements];
        int l = m1->IA[elements];
        matrix[l][k] = m1->A[elements];
        elements++;
    }
    elements = 0;
    for (int i = 0; i < m2->size; i++)
    {
        int k = mj2[elements];
        int l = m2->IA[elements];
        matrix[l][k] = matrix[l][k] + m2->A[elements];
        elements++;
    }

    te1 = tick();


    printf("\nTime of standart sum = %u\n\n", sum);
    printf("\nTime of sparse sum   = %lu\n\n", (te1 - tb1) / N);
    printf("\nPercent (standart of sparse) = %lu\n\n", 100*sum/((te1 - tb1) / N));

    struct SparseMatrix *res = malloc(sizeof(struct SparseMatrix));

    res->A = malloc(columns * rows * sizeof(int));
    res->IA = malloc(columns * rows * sizeof(int));
    res->JA = NULL;

    res->columns = columns;
    res->rows = rows;

    //for (int i = 0; i < rows; i++)
    //{
    //    for (int j = 0; j < columns; j++)
    //        printf("%d ", matrix_result[i][j]);
    //    printf("\n");
    //}

    int index = 0;
    for (int j = 0; j < columns; j++) {
        // create node for column j
        struct ElementNode *jNode = malloc(sizeof(struct ElementNode));
        jNode->index = -1;
        jNode->next = NULL;

        //printf("%d", (int)rows*columns*pr/100);
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] != 0) {
                int element = matrix[i][j];
                //printf("%d, %d\n", (int)rows*columns*pr/100, count);
                if (jNode->index < 0) {
                    jNode->index = index;
                }

                res->A[index] = element;
                res->IA[index] = i;

                // increase index
                index++;
                //printf("%d ", element);
            } else {
                //printf("0 ");
            }
        }

        addNode(res, jNode);
        //printf("\n");
    }


    res->size = index;

    res->A = realloc(res->A, index * sizeof(int));
    res->IA = realloc(res->IA, index * sizeof(int));

    return res;
}

struct SparseMatrix *manual(int rows, int columns) {
    struct SparseMatrix *matrix = malloc(sizeof(struct SparseMatrix));

    matrix->A = malloc(columns * rows * sizeof(int));
    matrix->IA = malloc(columns * rows * sizeof(int));
    matrix->JA = NULL;

    matrix->columns = columns;
    matrix->rows = rows;

    int quantity = 0;
    printf("Input quantity of elements: ");
    scanf("%d", &quantity);

    int matrix_result[rows][columns];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix_result[i][j] = 0;
    for (int i = 0; i < quantity; i++)
    {
        int element = 0;
        int x;
        int y;
        printf("\nInput element: ");
        scanf("%d", &element);
        printf("\nInput i: ");
        scanf("%d", &x);
        printf("\nInput j: ");
        scanf("%d", &y);
        matrix_result[y][x] = element;
    }

    //for (int i = 0; i < rows; i++)
    //{
    //    for (int j = 0; j < columns; j++)
    //        printf("%d ", matrix_result[i][j]);
    //    printf("\n");
    //}

    int index = 0;
    for (int j = 0; j < columns; j++) {
        // create node for column j
        struct ElementNode *jNode = malloc(sizeof(struct ElementNode));
        jNode->index = -1;
        jNode->next = NULL;

        //printf("%d", (int)rows*columns*pr/100);
        for (int i = 0; i < rows; i++) {
            if (matrix_result[i][j] != 0) {
                int element = matrix_result[i][j];
                //printf("%d, %d\n", (int)rows*columns*pr/100, count);
                if (jNode->index < 0) {
                    jNode->index = index;
                }

                matrix->A[index] = element;
                matrix->IA[index] = i;

                // increase index
                index++;
                //printf("%d ", element);
            } else {
                //printf("0 ");
            }
        }

        addNode(matrix, jNode);
        //printf("\n");
    }


    matrix->size = index;

    matrix->A = realloc(matrix->A, index * sizeof(int));
    matrix->IA = realloc(matrix->IA, index * sizeof(int));

    return matrix;
}
