#include "matrix.h"

matrix_t *generate_empty_matrix (unsigned int Height, unsigned int Width) {

    double *Values = calloc(Width * Height, sizeof(double));
    if (Values == NULL) {
        fprintf(stderr, "[!] Allocation for the data failed\n");
        return NULL;
    }

    matrix_t *Matrix = malloc(sizeof(matrix_t));
    if (Matrix == NULL) {
        free(Values);
        fprintf(stderr, "[!] Allocation for the matrix structure failed\n");
    return NULL;
    }

    Matrix->Width = Width;
    Matrix->Height = Height;
    Matrix->Values = Values;

    printf("[ ] Allocated a %d x %d matrix\n", Matrix->Height, Matrix->Width);
    return Matrix;
}

void free_matrix (matrix_t *Matrix) {
    if (Matrix != NULL) {
        if (Matrix->Values != NULL) {
            free(Matrix->Values);
            Matrix->Values = NULL;
        }
        free(Matrix);
    }
}

void print_matrix (matrix_t *Matrix) {

    if (Matrix == NULL) {
        fprintf(stderr, "[!] Error: can't access matrix");
        return;
    }

    int CurrentValue = 0;

    for (unsigned int i = 0; i < Matrix->Height; i++) {
        printf("[ ");
        for (unsigned int j = 0; j < Matrix->Width; j++) {
            printf("%10.6f ", Matrix->Values[CurrentValue]);
            CurrentValue++;
        }
        printf("]\n");
    }
}

double *get_row (matrix_t *Matrix, unsigned int RowIndex) {

    if (Matrix != NULL) {
        if (RowIndex < Matrix->Height) {
            return (Matrix->Values + RowIndex * Matrix->Width);
        } else {
            fprintf(stderr, "[!] Accessing (%d,:) in a %d x %d matrix\n", RowIndex, Matrix->Width, Matrix->Height);
        }
    }

    return NULL;

}

double get_element (matrix_t *Matrix, unsigned int RowIndex, unsigned int ColumnIndex) {

    if (Matrix != NULL) {
        if (RowIndex < Matrix->Height && ColumnIndex < Matrix->Width) {
            return Matrix->Values[RowIndex * Matrix->Width + ColumnIndex];
        } else {
            fprintf(stderr, "[!] Accessing (%d,%d) in a %d x %d matrix\n", RowIndex, ColumnIndex, Matrix->Width, Matrix->Height);
        } 
    }

    return NAN;

}

unsigned int get_matrix_length (matrix_t *Matrix) {

    if (Matrix != NULL) {
        return (Matrix->Width * Matrix->Height);
    }

    return 0;

}

void scale_row (matrix_t *Matrix, unsigned int RowIndex, double Scale) {

    if (Matrix != NULL) {
        double *Row = get_row (Matrix, RowIndex);
        if (Row != NULL) {
            for (unsigned int i = 0; i < Matrix->Width; i++) {
                Row[i] *= Scale;
            }
        }
    }
}

void subtract_row (matrix_t *Matrix, unsigned int RowIndex1, unsigned int RowIndex2) {

    if (Matrix != NULL) {
        double *Row1 = get_row (Matrix, RowIndex1);
        double *Row2 = get_row (Matrix, RowIndex2);

        if (Row1 != NULL && Row2 != NULL) {
            for (unsigned int i = 0; i < Matrix->Width; i++) {
                Row1[i] -= Row2[i];
            }
        }
    }
}

void swap_rows (matrix_t *Matrix, unsigned int RowIndex1, unsigned int RowIndex2) {

    if (Matrix != NULL) {
        double *Row1 = get_row(Matrix, RowIndex1);
        double *Row2 = get_row(Matrix, RowIndex2);

        if (Row1 != NULL && Row2 != NULL) {
            for (int i = 0; i < Matrix->Width; i++) {
                double Temp = Row2[i];
                Row2[i] = Row1[i];
                Row1[i] = Temp;
            }
        }
    }
}

void randomize_matrix (matrix_t *Matrix) {
    
    if (Matrix != NULL) {
        int MatrixLength = get_matrix_length(Matrix);
        for (unsigned int i = 0; i < MatrixLength; i++) {
            int RandomInt = rand();
            Matrix->Values[i] = (double) (RandomInt % 1000);
        }
    }
}

void gauss (matrix_t *Matrix, unsigned int RowIndex, unsigned int ColumnIndex) {
    
    if (Matrix != NULL) {
        
        if (Matrix->Height >= Matrix->Width) {
            fprintf(stderr, "[!] Error: Can't gauss matrix\n");
            return;
        }

        double FirstElement = get_element (Matrix, RowIndex, ColumnIndex);
        unsigned int Row = RowIndex + 1;

        while (FirstElement == 0) {
            swap_rows (Matrix, RowIndex, Row);
            FirstElement = get_element (Matrix, RowIndex, ColumnIndex);
            Row++;
            if (Row >= Matrix->Height) {
                fprintf(stderr, "[!] Error: Singular matrix!\n");
                return;
            }
        }

        scale_row (Matrix, RowIndex, 1/FirstElement);

        for (unsigned int i = 0; i < Matrix->Height; i++) {
            if (i != RowIndex) {   
                double *CurrentRow = get_row (Matrix, i);
                double Multiplier = CurrentRow[ColumnIndex];
                scale_row (Matrix, RowIndex, Multiplier);
                subtract_row (Matrix, i, RowIndex);
                scale_row (Matrix, RowIndex, 1/Multiplier);
            }
        }

        if (RowIndex < Matrix->Height - 1) {
            gauss (Matrix, RowIndex + 1, ColumnIndex + 1);
        }
    }
}

void solve_matrix (matrix_t *Matrix) {

    if (Matrix != NULL) {
        gauss (Matrix, 0, 0);

        printf("Solutions:\n");
        for (int i = 0; i < Matrix->Height; i++) {
            printf("X%d = %10.6f\n", i, Matrix->Values[((i + 1) * Matrix->Width) - 1]);
        }
    }
}


