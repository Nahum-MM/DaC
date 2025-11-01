#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para intercambiar dos elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función de partición tipo QuickSort (usa un pivote aleatorio)
int partition(int arr[], int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[right]);
    int storeIndex = left;

    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            swap(&arr[i], &arr[storeIndex]);
            storeIndex++;
        }
    }
    swap(&arr[storeIndex], &arr[right]);
    return storeIndex;
}

// Implementación recursiva de Quick Select
int quick_select(int arr[], int left, int right, int k) {
    if (left == right)
        return arr[left];

    int pivotIndex = left + rand() % (right - left + 1);
    pivotIndex = partition(arr, left, right, pivotIndex);

    if (k == pivotIndex)
        return arr[k];
    else if (k < pivotIndex)
        return quick_select(arr, left, pivotIndex - 1, k);
    else
        return quick_select(arr, pivotIndex + 1, right, k);
}

// Función para generar arreglo aleatorio con números únicos
void generar_arreglo(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;

    // Mezclar arreglo (Fisher-Yates)
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

// Función para probar Quick Select con medición de tiempo
void probar_quick_select(int n, int k) {
    int *arr = (int *)malloc(n * sizeof(int));
    generar_arreglo(arr, n);

    clock_t inicio = clock();
    int resultado = quick_select(arr, 0, n - 1, k);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tamano del arreglo: %d\n", n);
    printf("k = %d -> %d\n", k, resultado);
    printf("Tiempo de ejecucion: %.6f segundos\n\n", tiempo);

    free(arr);
}

int main() {
    srand(time(NULL));
    printf("==== Pruebas Quick Select ====\n\n");
    probar_quick_select(100, 50);
    probar_quick_select(1000, 500);
    probar_quick_select(100000, 50000);
    return 0;
    system("pause");
}