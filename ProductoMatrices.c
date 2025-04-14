#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para asignar memoria dinámicamente a una matriz
int** crearMatriz(int n) {
    int i;
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        matriz[i] = (int*)malloc(n * sizeof(int));
    }
    return matriz;
}

// Liberar la memoria de una matriz
void liberarMatriz(int** matriz, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Llenar una matriz con números aleatorios
void llenarMatriz(int** matriz, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
}

// Multiplicación tradicional
void multiplicarMatrices(int** A, int** B, int** C, int n) {
    int i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = 0;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
}

// Verificar si un número es potencia de 2
int esPotenciaDe2(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

int main() {
    int n;
    printf("Ingresa el valor de n (potencia de 2): ");
    scanf("%d", &n);

    if (!esPotenciaDe2(n)) {
        printf("Error: El valor debe ser una potencia de 2.\n");
        return 1;
    }

    srand(time(NULL));  // Semilla para números aleatorios

    int** A = crearMatriz(n);
    int** B = crearMatriz(n);
    int** C = crearMatriz(n);

    llenarMatriz(A, n);
    llenarMatriz(B, n);

    clock_t inicio = clock();
    multiplicarMatrices(A, B, C, n);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %f segundos\n", tiempo);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}

