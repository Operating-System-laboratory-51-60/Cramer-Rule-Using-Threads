#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <stdlib.h>
#include <math.h>

typedef struct Matrix
{
    int size;
    double **data;
} Matrix;

Matrix* create_matrix(int n)
{
    Matrix* m = (Matrix*) malloc (sizeof(Matrix));
    m->size = n;
    m->data = (double**)malloc(n * sizeof(double*));
    for(int i=0;i<n;i++) m->data[i] = (double*)malloc(n * sizeof(double));
    return m;
}

void free_matrix(Matrix *m)
{
    for(int i=0;i<m->size;i++) free(m->data[i]);
    free(m->data);
    free(m);
}

Matrix* copy_matrix(Matrix *src)
{
    Matrix *dest = create_matrix(src->size);
    for(int i=0;i<src->size;i++)
    {
        for(int j=0;j<src->size;j++)
            dest->data[i][j] = src->data[i][j];
    }
    return dest;
}

void fill_random_system(Matrix *A, double *B)
{
    int n = A->size;
    for(int i=0;i<n;i++)
    {
        B[i] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        for(int j=0;j<n;j++)
            A->data[i][j] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    }
}

void replace_column(Matrix *m, double *vec, int col_idx)
{
    for (int i = 0; i < m->size; i++) m->data[i][col_idx] = vec[i];
}

// Fast O(N^3) Gaussian Elimination Determinant
double fast_determinant(Matrix *m)
{
    Matrix *temp = copy_matrix(m);
    int n = temp->size;
    double det = 1.0;

    for(int i=0;i<n;i++)
    {
        int pivot = i;
        while(pivot < n && fabs(temp->data[pivot][i]) < 1e-9) pivot++;
        if(pivot == n)
        {
            free_matrix(temp);
            return 0.0;
        }
        
        if(pivot != i)
        {
            double *swap = temp->data[i];
            temp->data[i] = temp->data[pivot];
            temp->data[pivot] = swap;
            det = -det;
        }
        
        det *= temp->data[i][i];
        for(int j=i+1;j<n;j++)
        {
            double factor = temp->data[j][i] / temp->data[i][i];
            for(int k=i;k<n;k++) temp->data[j][k] -= factor * temp->data[i][k];
        }
    }
    free_matrix(temp);
    return det;
}

#endif
