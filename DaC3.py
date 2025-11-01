import random
import math
import time

def distancia(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def fuerza_bruta(puntos):
    min_dist = float('inf')
    par = (None, None)
    n = len(puntos)
    for i in range(n):
        for j in range(i + 1, n):
            d = distancia(puntos[i], puntos[j])
            if d < min_dist:
                min_dist = d
                par = (puntos[i], puntos[j])
    return par, min_dist

def distancia_en_strip(strip, d_min):
    min_dist = d_min
    par = (None, None)
    strip.sort(key=lambda p: p[1])

    for i in range(len(strip)):
        for j in range(i + 1, len(strip)):
            if (strip[j][1] - strip[i][1]) >= min_dist:
                break
            d = distancia(strip[i], strip[j])
            if d < min_dist:
                min_dist = d
                par = (strip[i], strip[j])
    return par, min_dist

def par_mas_cercano(puntos):
    if len(puntos) <= 3:
        return fuerza_bruta(puntos)

    mid = len(puntos) // 2
    mitad_izq = puntos[:mid]
    mitad_der = puntos[mid:]

    (p1, d1) = par_mas_cercano(mitad_izq)
    (p2, d2) = par_mas_cercano(mitad_der)

    d_min = min(d1, d2)
    par = p1 if d1 < d2 else p2

    x_medio = puntos[mid][0]
    strip = [p for p in puntos if abs(p[0] - x_medio) < d_min]

    (p3, d3) = distancia_en_strip(strip, d_min)
    if d3 < d_min:
        return p3, d3
    else:
        return par, d_min

def ejecutar_prueba(n):
    puntos = [(random.uniform(0, 10000), random.uniform(0, 10000)) for _ in range(n)]
    puntos.sort(key=lambda p: p[0])

    inicio = time.time()
    (par, dist) = par_mas_cercano(puntos)
    fin = time.time()

    print(f"\n🔹 Número de puntos: {n}")
    print(f"Par más cercano: {par}")
    print(f"Distancia mínima: {dist:.6f}")
    print(f"Tiempo de ejecución: {fin - inicio:.6f} segundos")
    
for n in [10, 100, 1000, 100000]:
    ejecutar_prueba(n)
