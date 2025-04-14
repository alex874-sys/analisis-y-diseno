#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para verificar si un número es potencia de 2
int esPotenciaDe2(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

// Función para crear una matriz dinámica
int** crearMatriz(int n) {
    int i;
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        matriz[i] = (int*)malloc(n * sizeof(int));
    }
    return matriz;
}

// Liberar matriz
void liberarMatriz(int** matriz, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Llenar matriz con números aleatorios
void llenarMatriz(int** matriz, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
}

// Suma de matrices
void sumar(int** A, int** B, int** C, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Resta de matrices
void restar(int** A, int** B, int** C, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Método Divide and Conquer
void multiplicarDaC(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int i, j;

    int mitad = n / 2;

    // Crear submatrices temporales
    int** A11 = crearMatriz(mitad);
    int** A12 = crearMatriz(mitad);
    int** A21 = crearMatriz(mitad);
    int** A22 = crearMatriz(mitad);
    int** B11 = crearMatriz(mitad);
    int** B12 = crearMatriz(mitad);
    int** B21 = crearMatriz(mitad);
    int** B22 = crearMatriz(mitad);
    int** C11 = crearMatriz(mitad);
    int** C12 = crearMatriz(mitad);
    int** C21 = crearMatriz(mitad);
    int** C22 = crearMatriz(mitad);
    int** temp1 = crearMatriz(mitad);
    int** temp2 = crearMatriz(mitad);

    // Dividir matrices en submatrices
    for (i = 0; i < mitad; i++) {
        for (j = 0; j < mitad; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mitad];
            A21[i][j] = A[i + mitad][j];
            A22[i][j] = A[i + mitad][j + mitad];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mitad];
            B21[i][j] = B[i + mitad][j];
            B22[i][j] = B[i + mitad][j + mitad];
        }
    }

    // C11 = A11*B11 + A12*B21
    multiplicarDaC(A11, B11, temp1, mitad);
    multiplicarDaC(A12, B21, temp2, mitad);
    sumar(temp1, temp2, C11, mitad);

    // C12 = A11*B12 + A12*B22
    multiplicarDaC(A11, B12, temp1, mitad);
    multiplicarDaC(A12, B22, temp2, mitad);
    sumar(temp1, temp2, C12, mitad);

    // C21 = A21*B11 + A22*B21
    multiplicarDaC(A21, B11, temp1, mitad);
    multiplicarDaC(A22, B21, temp2, mitad);
    sumar(temp1, temp2, C21, mitad);

    // C22 = A21*B12 + A22*B22
    multiplicarDaC(A21, B12, temp1, mitad);
    multiplicarDaC(A22, B22, temp2, mitad);
    sumar(temp1, temp2, C22, mitad);

    // Combinar submatrices en C
    for (i = 0; i < mitad; i++) {
        for (j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }
    }

    // Liberar memoria
    liberarMatriz(A11, mitad); liberarMatriz(A12, mitad);
    liberarMatriz(A21, mitad); liberarMatriz(A22, mitad);
    liberarMatriz(B11, mitad); liberarMatriz(B12, mitad);
    liberarMatriz(B21, mitad); liberarMatriz(B22, mitad);
    liberarMatriz(C11, mitad); liberarMatriz(C12, mitad);
    liberarMatriz(C21, mitad); liberarMatriz(C22, mitad);
    liberarMatriz(temp1, mitad); liberarMatriz(temp2, mitad);
}

int main() {
    int n;

    printf("Ingresa el valor de n (potencia de 2): ");
    scanf("%d", &n);

    if (!esPotenciaDe2(n)) {
        printf("Error: El valor debe ser una potencia de 2.\n");
        return 1;
    }

    srand(time(NULL));

    int** A = crearMatriz(n);
    int** B = crearMatriz(n);
    int** C = crearMatriz(n);

    llenarMatriz(A, n);
    llenarMatriz(B, n);

    clock_t inicio = clock();
    multiplicarDaC(A, B, C, n);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución (DaC): %f segundos\n", tiempo);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}

