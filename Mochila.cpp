#include <stdio.h>
#include <string.h>

#define MAX_OBJETOS 5
#define MAX_PESO 5

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int valores[] = {1500, 3000, 2000, 2000}; // G, S, L, I
    int pesos[] =   {1,    4,    3,    1};
    char *nombres[] = {"G", "S", "L", "I"};

    int n = 4; // número de objetos
    int W = 4; // capacidad máxima de la mochila

    int tabla[MAX_OBJETOS][MAX_PESO] = {0};
    char seleccion[MAX_OBJETOS][MAX_PESO][10];

    for (int i = 0; i < n; i++) {
        for (int w = 1; w <= W; w++) {
            if (pesos[i] <= w) {
                int sin_item = (i == 0) ? 0 : tabla[i - 1][w - 1];
                int con_item = valores[i] + ((i == 0 || (w - pesos[i]) <= 0) ? 0 : tabla[i - 1][w - pesos[i] - 1]);

                if (con_item > ((i == 0) ? 0 : tabla[i - 1][w - 1])) {
                    tabla[i][w - 1] = con_item;
                    if (i == 0 || (w - pesos[i]) <= 0) {
                        strcpy(seleccion[i][w - 1], nombres[i]);
                    } else {
                        strcpy(seleccion[i][w - 1], seleccion[i - 1][w - pesos[i] - 1]);
                        strcat(seleccion[i][w - 1], nombres[i]);
                    }
                } else {
                    tabla[i][w - 1] = (i == 0) ? 0 : tabla[i - 1][w - 1];
                    if (i > 0)
                        strcpy(seleccion[i][w - 1], seleccion[i - 1][w - 1]);
                }
            } else {
                tabla[i][w - 1] = (i == 0) ? 0 : tabla[i - 1][w - 1];
                if (i > 0)
                    strcpy(seleccion[i][w - 1], seleccion[i - 1][w - 1]);
            }
        }
    }

    // Imprimir tabla final
    printf("Tabla final (valor y selección):\n");
    for (int i = 0; i < n; i++) {
        for (int w = 0; w < W; w++) {
            printf("$%d\t%s\t", tabla[i][w], seleccion[i][w]);
        }
        printf("\n");
    }

    printf("\nMejor resultado: $%d con objetos %s\n", tabla[n - 1][W - 1], seleccion[n - 1][W - 1]);

    return 0;
}

