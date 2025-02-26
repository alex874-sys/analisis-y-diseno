#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int divide(int, int );


int main() {
    int dividendo, divisor;

    printf("Introduce el dividendo: ");
    scanf("%d", &dividendo);
    printf("Introduce el divisor: ");
    scanf("%d", &divisor);
    
    //llamamos a la funcion y le mandamos los argumentos dividendo y divisor ingresado por el usuario, guardando el valor en resultado
    int resultado = divide(dividendo, divisor);

    printf("El cociente de la división es: %d\n", resultado);

    return 0;
}


int divide(int dividendo, int divisor) {
    // Definimos los valores máximos y mínimos según el rango de 32 bits
    int MAX = INT_MAX;
    int MIN = INT_MIN;

    // restriccion de la division entre cero 
    if (divisor == 0) {
        printf("Error: El divisor no puede ser cero.\n");
        exit(1);  // Termina el programa con un error si el divisor es 0
    }

    if (dividendo == MIN && divisor == -1) {
        return MAX;  // Caso de overflow
    }

    // checamos si el resultado sera negativo comparando los signos de ambos valores
    int negativo = (dividendo < 0) != (divisor < 0);

    long long abs_dividendo = llabs(dividendo);
    long long abs_divisor = llabs(divisor);

    int cociente = 0;
    while (abs_dividendo >= abs_divisor) {
        long long temp = abs_divisor;
        int i = 1;
        while (abs_dividendo >= temp) {
            abs_dividendo -= temp;
            cociente += i;

            // duplicamos le visior
            i += i;
            temp += temp;
        }
    }

    // colocamos el signo 
    if (negativo) {
        cociente = -cociente;
    }

    // revisamos si el cociente esta dentro del rango 
    if (cociente > MAX) {
        return MAX;
    } else if (cociente < MIN) {
        return MIN;
    }

    return cociente;
}
