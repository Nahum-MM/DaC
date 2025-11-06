#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

long long mergeSortAndCount(int arr[], int temp[], int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        inv_count += mergeSortAndCount(arr, temp, left, mid);       
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right); 
        inv_count += mergeAndCount(arr, temp, left, mid, right);    
    }
    return inv_count;
}

void generarArreglo(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (n * 10) + 1;
}

void probarConteoInversiones() {
    int tamanios[] = {100, 1000, 100000};
    int numPruebas = sizeof(tamanios) / sizeof(tamanios[0]);

    for (int t = 0; t < numPruebas; t++) {
        int n = tamanios[t];
        int *arr = (int*)malloc(n * sizeof(int));
        int *temp = (int*)malloc(n * sizeof(int));

        generarArreglo(arr, n);

        clock_t inicio = clock();
        long long inversiones = mergeSortAndCount(arr, temp, 0, n - 1);
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("n = %-6d = Inversiones = %-12lld | Tiempo = %.6f segundos\n", n, inversiones, tiempo);

        free(arr);
        free(temp);
    }
}

int main() {
    srand(time(NULL));
    probarConteoInversiones();
    return 0;

}
