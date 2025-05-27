#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ARREGLOS 5       // Mínimo 5 arreglos
#define TAMANO_MAXIMO 20     // Tamaño máximo de cada arreglo
#define VALOR_MAXIMO 9       // Altura máxima aleatoria

int trap(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int left_max = 0;
    int right_max = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= left_max) {
                left_max = height[left];
            } else {
                water += left_max - height[left];
            }
            left++;
        } else {
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                water += right_max - height[right];
            }
            right--;
        }
    }

    return water;
}

void generarArregloAleatorio(int* arreglo, int tamano) {
    int i;
	for (i = 0; i < tamano; i++) {
        arreglo[i] = rand() % (VALOR_MAXIMO + 1);
    }
}

void imprimirArreglo(int* arreglo, int tamano) {
    int i;
	printf("[");
    for ( i = 0; i < tamano; i++) {
        printf("%d", arreglo[i]);
        if (i < tamano - 1) printf(", ");
    }
    printf("]");
}

int main() {
    srand(time(NULL));  // Inicializar generador de números aleatorios
	int i;
    for (i = 0; i < NUM_ARREGLOS; i++) {
        int tamano = (rand() % 16) + 5;  // Tamaño entre 5 y 20
        int* arreglo = (int*)malloc(tamano * sizeof(int));
        if (arreglo == NULL) {
            printf("Error al asignar memoria.\n");
            return 1;
        }

        generarArregloAleatorio(arreglo, tamano);
        printf("Arreglo %d: ", i + 1);
        imprimirArreglo(arreglo, tamano);
        int agua = trap(arreglo, tamano);
        printf(" ? Agua atrapada: %d\n", agua);

        free(arreglo);
    }

    return 0;
}


