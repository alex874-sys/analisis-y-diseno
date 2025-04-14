#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int esPotenciaDe2(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

int** crearMatriz(int n) {
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matriz[i] = (int*)malloc(n * sizeof(int));
    return matriz;
}

void liberarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void llenarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
}

void sumar(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void restar(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mitad = n / 2;

    // Crear submatrices
    int** A11 = crearMatriz(mitad);
    int** A12 = crearMatriz(mitad);
    int** A21 = crearMatriz(mitad);
    int** A22 = crearMatriz(mitad);
    int** B11 = crearMatriz(mitad);
    int** B12 = crearMatriz(mitad);
    int** B21 = crearMatriz(mitad);
    int** B22 = crearMatriz(mitad);
    int** M1 = crearMatriz(mitad);
    int** M2 = crearMatriz(mitad);
    int** M3 = crearMatriz(mitad);
    int** M4 = crearMatriz(mitad);
    int** M5 = crearMatriz(mitad);
    int** M6 = crearMatriz(mitad);
    int** M7 = crearMatriz(mitad);
    int** T1 = crearMatriz(mitad);
    int** T2 = crearMatriz(mitad);

    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
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

    // M1 = (A11 + A22)(B11 + B22)
    sumar(A11, A22, T1, mitad);
    sumar(B11, B22, T2, mitad);
    strassen(T1, T2, M1, mitad);

    // M2 = (A21 + A22)B11
    sumar(A21, A22, T1, mitad);
    strassen(T1, B11, M2, mitad);

    // M3 = A11(B12 - B22)
    restar(B12, B22, T1, mitad);
    strassen(A11, T1, M3, mitad);

    // M4 = A22(B21 - B11)
    restar(B21, B11, T1, mitad);
    strassen(A22, T1, M4, mitad);

    // M5 = (A11 + A12)B22
    sumar(A11, A12, T1, mitad);
    strassen(T1, B22, M5, mitad);

    // M6 = (A21 - A11)(B11 + B12)
    restar(A21, A11, T1, mitad);
    sumar(B11, B12, T2, mitad);
    strassen(T1, T2, M6, mitad);

    // M7 = (A12 - A22)(B21 + B22)
    restar(A12, A22, T1, mitad);
    sumar(B21, B22, T2, mitad);
    strassen(T1, T2, M7, mitad);

    // C11 = M1 + M4 - M5 + M7
    sumar(M1, M4, T1, mitad);
    restar(T1, M5, T2, mitad);
    sumar(T2, M7, T1, mitad);
    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++)
            C[i][j] = T1[i][j];

    // C12 = M3 + M5
    sumar(M3, M5, T1, mitad);
    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++)
            C[i][j + mitad] = T1[i][j];

    // C21 = M2 + M4
    sumar(M2, M4, T1, mitad);
    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++)
            C[i + mitad][j] = T1[i][j];

    // C22 = M1 - M2 + M3 + M6
    restar(M1, M2, T1, mitad);
    sumar(T1, M3, T2, mitad);
    sumar(T2, M6, T1, mitad);
    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++)
            C[i + mitad][j + mitad] = T1[i][j];

    // Liberar matrices
    liberarMatriz(A11, mitad); liberarMatriz(A12, mitad);
    liberarMatriz(A21, mitad); liberarMatriz(A22, mitad);
    liberarMatriz(B11, mitad); liberarMatriz(B12, mitad);
    liberarMatriz(B21, mitad); liberarMatriz(B22, mitad);
    liberarMatriz(M1, mitad); liberarMatriz(M2, mitad);
    liberarMatriz(M3, mitad); liberarMatriz(M4, mitad);
    liberarMatriz(M5, mitad); liberarMatriz(M6, mitad);
    liberarMatriz(M7, mitad); liberarMatriz(T1, mitad);
    liberarMatriz(T2, mitad);
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
    strassen(A, B, C, n);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución (Strassen): %f segundos\n", tiempo);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}

