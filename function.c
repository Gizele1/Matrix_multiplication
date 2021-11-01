#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function.h"

struct mat generate(int row, int col, float matrix[])
{
    struct mat *mat1;
    mat1 = (struct mat *)malloc(sizeof(struct mat));
    mat1->matrix = (float *)malloc(sizeof(float) * row * col);
    mat1->col = col;
    mat1->row = row;
    mat1->matrix = &matrix[0];
    return *mat1;
}

struct mat generateR(int row, int col)
{
    struct mat *mat1;
    mat1 = (struct mat *)malloc(sizeof(struct mat *));
    mat1->matrix = (float *)malloc(sizeof(float) * row * col);
    mat1->col = col;
    mat1->row = row;
    srand(time(0));
    for (int i = 0; i < col * row; i++)
    {
        *mat1->matrix = (rand() % 100) / 1.2f;
        mat1->matrix++;
    }
    mat1->matrix = mat1->matrix - col * row;
    return *mat1;
}

void deletemat(struct mat *mat)
{
    free(mat);
}

struct mat copymat(struct mat mat1)
{
    struct mat *mat2;
    mat2 = (struct mat *)malloc(sizeof(struct mat *));
    mat2->matrix = (float *)malloc(sizeof(float) * mat1.col * mat1.row);
    mat2->col = mat1.col;
    mat2->row = mat1.row;
    for (int i = 0; i < (mat1.col) * (mat1.row); i++)
    {
        *mat2->matrix = *mat1.matrix;
        mat1.matrix++;
        mat2->matrix++;
    }
    mat1.matrix = mat1.matrix - mat1.col * mat1.row;
    mat2->matrix = mat2->matrix - mat1.col * mat1.row;
    return *mat2;
}

struct mat mulmat(struct mat mat1, struct mat mat2)
{
    struct mat *mat3;
    mat3 = (struct mat *)malloc(sizeof(struct mat));
    mat3->matrix = (float *)malloc(sizeof(float) * mat1.row * mat2.col);

    if (mat1.col == mat2.row)
    {
        mat3->row = mat1.row;
        mat3->col = mat2.col;
        int m = mat1.row;
        int n = mat2.col;
        int p = mat1.col;
        for (int i = 0; i < m; i++)
        {
            for (int k = 0; k < p; k++)
            {
                float r = mat1.matrix[i * n + k];
                for (int j = 0; j < n; j++)
                {
                    mat3->matrix[i * n + j] += r * mat2.matrix[k * n + j];
                }
            }
        }
    }
    else
    {
        printf("warning!the dimension do not fit.");
    }
    return *mat3;
}

inline float getvalueofmat(int i, int j, struct mat mat)
{
    float value = 0.f;
    int row = mat.row;
    int col = mat.col;
    int index = i * col + j;
    mat.matrix = mat.matrix + index;
    value = *mat.matrix;
    mat.matrix = mat.matrix - index;
    return value;
}

inline void setvalueofmat(int i, int j, float value, struct mat *mat)
{

    int col = mat->col;
    int index = i * col + j;
    mat->matrix = mat->matrix + index;
    *mat->matrix = value;
    mat->matrix = mat->matrix - index;
}