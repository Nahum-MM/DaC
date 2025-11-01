#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

typedef struct {
    double x;
    double y;
} Punto;

double distancia(Punto p1, Punto p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

double fuerza_bruta(Punto puntos[], int n, Punto *p1, Punto *p2) {
    double min_dist = DBL_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = distancia(puntos[i], puntos[j]);
            if (d < min_dist) {
                min_dist = d;
                *p1 = puntos[i];
                *p2 = puntos[j];
            }
        }
    }
    return min_dist;
}

int compararX(const void *a, const void *b) {
    Punto *p1 = (Punto *)a;
    Punto *p2 = (Punto *)b;
    if (p1->x < p2->x) return -1;
    else if (p1->x > p2->x) return 1;
    else return 0;
}

int compararY(const void *a, const void *b) {
    Punto *p1 = (Punto *)a;
    Punto *p2 = (Punto *)b;
    if (p1->y < p2->y) return -1;
    else if (p1->y > p2->y) return 1;
    else return 0;
}

double distancia_en_strip(Punto strip[], int size, double d_min, Punto *p1, Punto *p2) {
    double min = d_min;
    qsort(strip, size, sizeof(Punto), compararY);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            double d = distancia(strip[i], strip[j]);
            if (d < min) {
                min = d;
                *p1 = strip[i];
                *p2 = strip[j];
            }
        }
    }
    return min;
}

double par_mas_cercano(Punto puntos[], int n, Punto *p1, Punto *p2) {
    if (n <= 3)
        return fuerza_bruta(puntos, n, p1, p2);

    int mid = n / 2;
    Punto p_izq1, p_izq2, p_der1, p_der2;
    double d_izq = par_mas_cercano(puntos, mid, &p_izq1, &p_izq2);
    double d_der = par_mas_cercano(puntos + mid, n - mid, &p_der1, &p_der2);

    double d_min;
    if (d_izq < d_der) {
        d_min = d_izq;
        *p1 = p_izq1;
        *p2 = p_izq2;
    } else {
        d_min = d_der;
        *p1 = p_der1;
        *p2 = p_der2;
    }

    double x_medio = puntos[mid].x;
    Punto *strip = (Punto *)malloc(n * sizeof(Punto));
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(puntos[i].x - x_medio) < d_min)
            strip[j++] = puntos[i];
    }

    Punto p3, p4;
    double d_strip = distancia_en_strip(strip, j, d_min, &p3, &p4);
    if (d_strip < d_min) {
        *p1 = p3;
        *p2 = p4;
        d_min = d_strip;
    }

    free(strip);
    return d_min;
}

void ejecutar_prueba(int n) {
    Punto *puntos = (Punto *)malloc(n * sizeof(Punto));
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        puntos[i].x = ((double)rand() / RAND_MAX) * 10000.0;
        puntos[i].y = ((double)rand() / RAND_MAX) * 10000.0;
    }

    qsort(puntos, n, sizeof(Punto), compararX);

    Punto p1, p2;
    clock_t inicio = clock();
    double dist = par_mas_cercano(puntos, n, &p1, &p2);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("\nNumero de puntos: %d\n", n);
    printf("Par mas cercano: (%.2f, %.2f) y (%.2f, %.2f)\n", p1.x, p1.y, p2.x, p2.y);
    printf("Distancia minima: %.6f\n", dist);
    printf("Tiempo de ejecucion: %.6f segundos\n", tiempo);

    free(puntos);
}

int main() {
    int tamanos[] = {10, 100, 1000, 100000};
    int n_tests = sizeof(tamanos) / sizeof(tamanos[0]);

    for (int i = 0; i < n_tests; i++) {
        ejecutar_prueba(tamanos[i]);
    }

    return 0;
}
