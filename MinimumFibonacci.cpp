/**
 * Problema: Minimum Fibonacci Terms with Sum Equal to K
 * Alumno: Cervantes Contreras Alexis
 * 
 * Encuentra el minimo numero de terminos de Fibonacci distintos que sumen exactamente
 * un valor dado K. Los terminos deben ser no consecutivos en la secuencia de Fibonacci
 * y no pueden repetirse.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Funcion para verificar si un numero es primo
bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Funcion para calcular el valor de K basado en la fecha de nacimiento
int calcularK(int dia, int mes, int anio) {
    // K = (día * 100) + (mes * 10) + (año % 100)
    return (dia * 100) + (mes * 10) + (anio % 100);
}

// Funcion para generar la secuencia de Fibonacci modificada
void generarFibonacciModificado(int K, int *fibArray, int *tamano) {
    int a = 0, b = 1;
    int posicion = 1;
    
    // Agregar el primer termino (0)
    fibArray[0] = a;
    *tamano = 1;
    
    // Agregar el segundo y tercer termino (1, 1)
    fibArray[1] = b;
    fibArray[2] = b;
    *tamano = 3;
    posicion = 3;
    
    int c;
    while (true) {
        posicion++;
        c = a + b;
        a = b;
        b = c;
        
        // Si el termino actual es mayor que K, terminamos
        if (c > K) break;
        
        // Si la posicion no es prima, agregamos el término
        if (!esPrimo(posicion)) {
            fibArray[*tamano] = c;
            (*tamano)++;
        }
    }
}

// Funcion para encontrar el minimo numero de terminos para la suma K
int encontrarTerminosMinimos(int K, int *fibArray, int tamano, int *terminos, int *numTerminos) {
    // Inicializamos con 0 términos usados
    *numTerminos = 0;
    
    // Utilizamos un enfoque greedy (ávido): siempre tomamos el termino más grande posible
    for (int i = tamano - 1; i >= 0 && K > 0; i--) {
        if (fibArray[i] <= K) {
            terminos[*numTerminos] = fibArray[i];
            (*numTerminos)++;
            K -= fibArray[i];
        }
    }
    
    // Si K es 0, hemos encontrado una solución
    return (K == 0) ? *numTerminos : -1;
}

// Función para mostrar los resultados
void mostrarResultados(int K, int *fibArray, int tamano, int *terminos, int numTerminos) {
    printf("K = %d\n\n", K);
    
    printf("Secuencia de Fibonacci filtrada (sin terminos en posiciones primas):\n");
    for (int i = 0; i < tamano; i++) {
        printf("%d", fibArray[i]);
        if (i < tamano - 1) printf(", ");
    }
    printf("\n\n");
    
    if (numTerminos > 0) {
        printf("Solucion optima:\n");
        for (int i = 0; i < numTerminos; i++) {
            printf("%d", terminos[i]);
            if (i < numTerminos - 1) printf(" + ");
        }
        printf(" = %d ? %d terminos.\n", K, numTerminos);
    } else {
        printf("No se encontro solucion.\n");
    }
}

int main() {
    int dia, mes, anio;
    
    // Solicitar la fecha de nacimiento
    printf("Ingrese su fecha de nacimiento:\n");
    printf("Dia (1-31): ");
    scanf("%d", &dia);
    printf("Mes (1-12): ");
    scanf("%d", &mes);
    printf("Anio (ej. 1995): ");
    scanf("%d", &anio);
    
    // Calcular K
    int K = calcularK(dia, mes, anio);
    
    // Generar la secuencia de Fibonacci modificada
    int fibArray[100]; // Asumimos un tamaño máximo razonable
    int tamano = 0;
    generarFibonacciModificado(K, fibArray, &tamano);
    
    // Encontrar los términos mínimos
    int terminos[100]; // Asumimos un tamaño máximo razonable
    int numTerminos = 0;
    encontrarTerminosMinimos(K, fibArray, tamano, terminos, &numTerminos);
    
    // Mostrar los resultados
    mostrarResultados(K, fibArray, tamano, terminos, numTerminos);
    
    // Explicación de la complejidad del algoritmo
    printf("\nExplicacion de complejidad:\n");
    printf("El algoritmo tiene complejidad O(log K) porque:\n");
    printf("1. La generacion de la secuencia de Fibonacci crece logaritmicamente con K\n");
    printf("2. La busqueda de los terminos minimos es proporcional al numero de terminos\n");
    printf("   en la secuencia, que es O(log K)\n");
    
    return 0;
}
