import random
import time

def quick_select(arr, k):
    if len(arr) == 1:
        return arr[0]
    
    pivot = random.choice(arr)
    menores = [x for x in arr if x < pivot]
    iguales  = [x for x in arr if x == pivot]
    mayores  = [x for x in arr if x > pivot]
    
    if k < len(menores):
        return quick_select(menores, k)
    elif k < len(menores) + len(iguales):
        return pivot
    else:
        return quick_select(mayores, k - len(menores) - len(iguales))

def probar_quick_select(n, k):
    arr = random.sample(range(1, n * 10), n)
    inicio = time.time()
    resultado = quick_select(arr, k)
    fin = time.time()
    print(f"Tamano del arreglo: {n}")
    print(f"k = {k} -> {resultado}")
    print(f"Tiempo de ejecucion: {fin - inicio:.6f} segundos\n")

print("==== Pruebas Quick Select ====\n")
probar_quick_select(100, 50)
probar_quick_select(1000, 500)
probar_quick_select(100000, 50000)
