#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LEN 30

// Estructura para almacenar resultados memorizados
typedef struct {
    char s1[MAX_LEN + 1];
    char s2[MAX_LEN + 1];
    bool result;
    bool valid;
} MemoEntry;

MemoEntry memo[10000];  // Tamaño de la tabla de memoización
int memo_size = 0;

// Función para ordenar cadenas (para comparar si tienen los mismos caracteres)
void sort_string(char *str) {
	int i,j;
    int len = strlen(str);
    for ( i = 0; i < len - 1; ++i) {
        for (j = i + 1; j < len; ++j) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

// Buscar en la tabla de memoización
bool get_memo(const char *s1, const char *s2, bool *result) {
	int i;
    for ( i = 0; i < memo_size; ++i) {
        if (memo[i].valid && strcmp(memo[i].s1, s1) == 0 && strcmp(memo[i].s2, s2) == 0) {
            *result = memo[i].result;
            return true;
        }
    }
    return false;
}

// Guardar en la tabla de memoización
void set_memo(const char *s1, const char *s2, bool result) {
    strcpy(memo[memo_size].s1, s1);
    strcpy(memo[memo_size].s2, s2);
    memo[memo_size].result = result;
    memo[memo_size].valid = true;
    memo_size++;
}

// Función recursiva principal
bool es_mezcla(const char *s1, const char *s2) {
    if (strcmp(s1, s2) == 0) return true;
    if (strlen(s1) != strlen(s2)) return false;

    bool memo_result;
    if (get_memo(s1, s2, &memo_result)) return memo_result;

    int len = strlen(s1);

    // Verificar si tienen los mismos caracteres
    char sorted1[MAX_LEN + 1], sorted2[MAX_LEN + 1];
    strcpy(sorted1, s1);
    strcpy(sorted2, s2);
    sort_string(sorted1);
    sort_string(sorted2);
    if (strcmp(sorted1, sorted2) != 0) {
        set_memo(s1, s2, false);
        return false;
    }

    // Probar todas las divisiones posibles
    int i;
    for ( i = 1; i < len; ++i) {
        char s1_left[MAX_LEN + 1], s1_right[MAX_LEN + 1];
        char s2_left[MAX_LEN + 1], s2_right[MAX_LEN + 1];
        char s2_swap_left[MAX_LEN + 1], s2_swap_right[MAX_LEN + 1];

        strncpy(s1_left, s1, i); s1_left[i] = '\0';
        strcpy(s1_right, s1 + i);

        strncpy(s2_left, s2, i); s2_left[i] = '\0';
        strcpy(s2_right, s2 + i);

        strncpy(s2_swap_left, s2 + len - i, i); s2_swap_left[i] = '\0';
        strncpy(s2_swap_right, s2, len - i); s2_swap_right[len - i] = '\0';

        // Sin intercambio
        if (es_mezcla(s1_left, s2_left) && es_mezcla(s1_right, s2_right)) {
            set_memo(s1, s2, true);
            return true;
        }
        // Con intercambio
        if (es_mezcla(s1_left, s2_swap_left) && es_mezcla(s1_right, s2_swap_right)) {
            set_memo(s1, s2, true);
            return true;
        }
    }

    set_memo(s1, s2, false);
    return false;
}

int main() {
    char s1[MAX_LEN + 1], s2[MAX_LEN + 1];

    strcpy(s1, "great");
    strcpy(s2, "rgeat");

    if (es_mezcla(s1, s2)) {
        printf("'%s' ES una mezcla de '%s'\n", s2, s1);
    } else {
        printf("'%s' NO es una mezcla de '%s'\n", s2, s1);
    }

    return 0;
}
