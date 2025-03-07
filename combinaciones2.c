#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Este arreglo asocia cada numero, incluyendo el 0 y 1 a sus respectivas letras., si metemos un numero, ese numero representara el indice 
const char *phoneMap[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};


//esta funcion construye las conbinaciones 
void generateCombinations(char *digits, int index, char *current, char **result, int *count) {
	int i;
    if (!digits[index]) {
    	//almacenamos una copia 
    	//incrementamos el contador para contar la combinacion creada
        result[(*count)++] = strdup(current);
        return;
    }
    //convierte el carácter en un número entero
    //obtiene las letras correspondientes al dígito actual.
	//Se recorre cada letra del grupo y se asigna a current[index].
	//Se llama recursivamente a generateCombinations con index + 1 para avanzar al siguiente número.
    for (i = 0; phoneMap[digits[index] - '0'][i]; i++) {
        current[index] = phoneMap[digits[index] - '0'][i];
        generateCombinations(digits, index + 1, current, result, count);
    }
}

char **letterCombinations(char *digits, int *returnSize) {
	int i;
	//Si digits es una cadena vacía (""), returnSize se pone en 0 y se retorna NULL.
    if (!*digits) return *returnSize = 0, NULL;
    int maxCombinations = 1;
    for (i = 0; digits[i]; i++) maxCombinations *= strlen(phoneMap[digits[i] - '0']);
    char **result = malloc(maxCombinations * sizeof(char *));
    char current[5] = {0};
    int count = 0;
    generateCombinations(digits, 0, current, result, &count);
    return *returnSize = count, result;
}

int main() {
	int i;
    char digits[5];
    printf("Ingrese los digitos: ");
    scanf("%4s", digits);
    int returnSize;
    char **combinations = letterCombinations(digits, &returnSize);
    for (i = 0; i < returnSize; i++) printf("%s\n", combinations[i]), free(combinations[i]);
    free(combinations);
    return 0;
}
