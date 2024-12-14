#ifndef MATRIX_H
#define MATRIX_F

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {

    unsigned int Width;
    unsigned int Height;

    double *Values;

} matrix_t;

matrix_t *generate_empty_matrix (unsigned int Height, unsigned int Width);

void free_matrix (matrix_t *Matrix);

void print_matrix (matrix_t *Matrix);

double *get_row (matrix_t *Matrix, unsigned int RowIndex);

double get_element (matrix_t *Matrix, unsigned int RowIndex, unsigned int ColumnIndex);

unsigned int get_matrix_length (matrix_t *Matrix);

void scale_row (matrix_t *Matrix, unsigned int RowIndex, double Scale);

void subtract_row (matrix_t *Matrix, unsigned int RowIndex1, unsigned int RowIndex2);

void swap_rows (matrix_t *Matrix, unsigned int RowIndex1, unsigned int RowIndex2);

void randomize_matrix (matrix_t *Matrix);

void gauss (matrix_t *Matrix, unsigned int RowIndex, unsigned int ColumnIndex);

void solve_matrix (matrix_t *Matrix);

#endif