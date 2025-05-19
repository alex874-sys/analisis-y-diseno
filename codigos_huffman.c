#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

void mostrarTextoCodificado(const char *); 

// Nodo del árbol de Huffman
typedef struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

// Min Heap
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    MinHeapNode** array;
} MinHeap;

// Crear nuevo nodo
MinHeapNode* newNode(char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Crear Min Heap
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**) malloc(minHeap->capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Intercambiar nodos
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[--minHeap->size];
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    int i = minHeap->size++;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for ( i = (n - 1) / 2; i >= 0; i--)
        minHeapify(minHeap, i);
}

// Verifica hoja
int isLeaf(MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// Crear heap y construir el árbol
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    int i;
    for (i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Construir el árbol de Huffman
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Almacenar códigos
void storeCodes(MinHeapNode* root, char* code, int top, char* codes[256]) {
    if (root->left) {
        code[top] = '0';
        storeCodes(root->left, code, top + 1, codes);
    }

    if (root->right) {
        code[top] = '1';
        storeCodes(root->right, code, top + 1, codes);
    }

    if (isLeaf(root)) {
        code[top] = '\0';
        codes[(unsigned char) root->data] = strdup(code);
    }
}

// Nueva función para imprimir tabla de códigos
void imprimirCodigosHuffman(char* codes[256]) {
	int i;
    printf("\nCódigos Huffman:\n");
    for (i = 0; i < 256; i++) {
        if (codes[i]) {
            printf("'%c': %s\n", i, codes[i]);
        }
    }
}


// Contar frecuencias
void countFrequencies(const char* text, int* freq, char* uniqueChars, int* uniqueCount) {
    int used[256] = {0};
    int i;
    for (i = 0; text[i]; i++) {
        unsigned char c = text[i];
        freq[c]++;
        if (!used[c]) {
            uniqueChars[(*uniqueCount)++] = c;
            used[c] = 1;
        }
    }
}

// Codificar texto
void encodeText(const char* text, char* codes[256], char* encodedText) {
	int i;
    for (i = 0; text[i]; i++) {
        strcat(encodedText, codes[(unsigned char) text[i]]);
    }
}
void mostrarTextoCodificado(const char* encodedText) {
    printf("\nTexto codificado:\n%s\n", encodedText);
}

// Decodificar
void decodeText(MinHeapNode* root, const char* encodedText, char* decodedText) {
    MinHeapNode* curr = root;
    int idx = 0;
    int i;
    for ( i = 0; encodedText[i]; i++) {
        curr = (encodedText[i] == '0') ? curr->left : curr->right;

        if (isLeaf(curr)) {
            decodedText[idx++] = curr->data;
            curr = root;
        }
    }
    decodedText[idx] = '\0';
}

// Calcular tamaño en bits
int calcOriginalBits(const char* text) {
    return strlen(text) * 8;
}

int calcEncodedBits(const char* encodedText) {
    return strlen(encodedText);
}

void imprimirFrecuencias(int freq[256]) {
	int i;
    printf("\nFrecuencias de caracteres:\n");
    for ( i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c' (%d): %d\n", isprint(i) ? i : '.', i, freq[i]);
        }
    }
}

// --------- MAIN ---------
int main() {
    FILE *fp = fopen("archivo.txt", "r");
    if (!fp) {
        perror("No se pudo abrir archivo.txt");
        return 1;
    }

    char text[10000], c;
    int i = 0;
    while ((c = fgetc(fp)) != EOF)
        text[i++] = c;
    text[i] = '\0';
    fclose(fp);

    int freq[256] = {0}, uniqueCount = 0;
    char uniqueChars[256];
    countFrequencies(text, freq, uniqueChars, &uniqueCount);
    imprimirFrecuencias(freq);

    int freqs[256];
    for (i = 0; i < uniqueCount; i++)
        freqs[i] = freq[(unsigned char)uniqueChars[i]];

    MinHeapNode* root = buildHuffmanTree(uniqueChars, freqs, uniqueCount);

    char* codes[256] = {0};
    char code[256];
    storeCodes(root, code, 0, codes);

    char encodedText[100000] = "";
    encodeText(text, codes, encodedText);
    mostrarTextoCodificado(encodedText);

    FILE* out = fopen("codificado.txt", "w");
    fputs(encodedText, out);
    fclose(out);

    int originalBits = calcOriginalBits(text);
    int compressedBits = calcEncodedBits(encodedText);

    printf("Tamaño original: %d bits\n", originalBits);
    printf("Tamaño comprimido: %d bits\n", compressedBits);
    printf("Tasa de compresión: %.2f%%\n", 100.0 * compressedBits / originalBits);

    // Decodificación
    FILE* codificado = fopen("codificado.txt", "r");
    if (!codificado) {
        perror("No se pudo abrir codificado.txt");
        return 1;
    }

    char codificadoText[100000];
    fgets(codificadoText, sizeof(codificadoText), codificado);
    fclose(codificado);

    char decodedText[10000];
    decodeText(root, codificadoText, decodedText);
    printf("\nTexto decodificado:\n%s\n", decodedText);
    
    imprimirCodigosHuffman(codes);
    return 0;
}

