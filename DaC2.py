import random
import time

def merge_count(arr):
    """
    Cuenta el número de inversiones en un arreglo usando el enfoque de Merge Sort.
    Una inversión es un par (i, j) tal que i < j y arr[i] > arr[j].
    """
    if len(arr) <= 1:
        return arr, 0
    
    mid = len(arr) // 2

    left, inv_left = merge_count(arr[:mid])
    right, inv_right = merge_count(arr[mid:])
    
    merged = []
    i = j = 0
    inv_count = inv_left + inv_right
    
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:

            merged.append(right[j])
            j += 1
            inv_count += len(left) - i

    merged += left[i:]
    merged += right[j:]
    
    return merged, inv_count

def probar_conteo_inversiones():

    tamanios = [1000, 10000, 50000, 100000] 
    
    print("--- Prueba de Rendimiento del Conteo de Inversiones (Merge Sort O(n log n)) ---")
    print(f"{'Tamaño (n)':<12} | {'Inversiones':<15} | {'Tiempo (segundos)':<20}")
    print("---------------------------------------------------------------------")
    
    for n in tamanios:
        arr = random.sample(range(n * 2), n) 
        
        inicio = time.time()
        _, inversiones = merge_count(arr)
        fin = time.time()
        
        print(f"{n:<12} | {inversiones:<15} | {fin - inicio:.6f}")

if __name__ == "__main__":

    probar_conteo_inversiones()
