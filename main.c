#include "matrix.h"

int main () {

    printf("Enter matrix size:\n");
    int Size = 0;
    scanf("%d", &Size);

    if (Size <= 0) {
        fprintf(stderr, "[!] Error: size can't be less than 1!\n");
        return EXIT_FAILURE;
    }

    matrix_t *Matrix = generate_empty_matrix(Size, Size + 1);

    if (Matrix == NULL) {
        fprintf(stderr, "[!] Error: memory allocation for matrix failed!");
        return EXIT_FAILURE;
    }

    printf("Enter randomization seed:\n");
    int Seed = 0;
    scanf("%d", &Seed);
    srand(Seed);

    randomize_matrix(Matrix);

    printf("Generated a %d x %d matrix of random values:\n", Size, Size + 1);
    print_matrix(Matrix);
    printf("\n");

    printf("Matrix solutions:\n");

    solve_matrix(Matrix);

    print_matrix(Matrix);

    free_matrix(Matrix);

    return EXIT_SUCCESS;
}