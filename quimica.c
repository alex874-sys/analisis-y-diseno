#include <stdio.h>
#include <stdlib.h>

// Función para comparar dos enteros (usada en qsort)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Función para calcular la suma de la química de los equipos y mostrar los equipos formados
long long total_chemistry(int* skill, int skillSize) {
    // Ordenamos el array de habilidades
    qsort(skill, skillSize, sizeof(int), compare);
    int i;
    // Calculamos la suma total de habilidades
    long long total_sum = 0;
    for (i = 0; i < skillSize; i++) {
        total_sum += skill[i];
    }
    
    // Verificamos si la suma total es divisible por el número de equipos
    int num_teams = skillSize / 2;
    if (total_sum % num_teams != 0) {
        return -1;
    }
    
    // Calculamos la suma deseada para cada equipo
    long long team_sum = total_sum / num_teams;
    
    // Inicializamos la suma total de química
    long long total_chemistry_sum = 0;
    
    // Usamos dos punteros para formar los equipos
    int left = 0;
    int right = skillSize - 1;
    
    // Mostrar los equipos formados
    printf("Equipos formados:\n");
    while (left < right) {
        // Verificamos si la suma de las habilidades de los dos jugadores es igual a team_sum
        if (skill[left] + skill[right] != team_sum) {
            return -1;
        }
        
        // Mostrar el equipo formado
        printf("Equipo: %d y %d (Habilidades: %d y %d)\n", left + 1, right + 1, skill[left], skill[right]);
        
        // Calculamos la química del equipo y la sumamos
        total_chemistry_sum += (long long)skill[left] * skill[right];
        
        // Movemos los punteros
        left++;
        right--;
    }
    
    return total_chemistry_sum;
}

int main() {
    int skillSize;
    
    // Solicitar al usuario el tamaño del array
    printf("Ingrese el numero de jugadores, debe ser numero par sino terminara el programa: ");
    scanf("%d", &skillSize);
    
    // Verificar que el tamaño sea par
    if (skillSize % 2 != 0) {
        printf("El numero de jugadores debe ser par.\n");
        return 1; // Salir del programa con código de error
    }
    
    // Crear el array de habilidades
    int* skill = (int*)malloc(skillSize * sizeof(int));
    if (skill == NULL) {
        printf("Error al asignar memoria.\n");
        return 1; // Salir del programa con código de error
    }
    int i;
    // Solicitar al usuario que ingrese las habilidades
    printf("Ingrese las habilidades de los %d jugadores:\n", skillSize);
    for (i = 0; i < skillSize; i++) {
        printf("Habilidad del jugador %d: ", i + 1);
        scanf("%d", &skill[i]);
    }
    
    // Calcular la suma de la química de los equipos y mostrar los equipos formados
    long long result = total_chemistry(skill, skillSize);
    
    // Mostrar el resultado
    if (result == -1) {
        printf("No es posible dividir a los jugadores en equipos con habilidades iguales.\n");
    } else {
        printf("La suma de la química de todos los equipos es: %lld\n", result);
    }
    
    // Liberar la memoria asignada
    free(skill);
    
    return 0;
}
