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
    
    # 1. División y conteo recursivo en las mitades
    left, inv_left = merge_count(arr[:mid])
    right, inv_right = merge_count(arr[mid:])
    
    merged = []
    i = j = 0
    # Inicializa el contador total con las inversiones internas
    inv_count = inv_left + inv_right
    
    # 2. Fusión y conteo de inversiones entre mitades (Split Inversions)
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            # Si right[j] es menor que left[i], forma una inversión
            # con left[i] y todos los elementos restantes en la lista izquierda.
            merged.append(right[j])
            j += 1
            inv_count += len(left) - i
    
    # 3. Añadir elementos restantes
    merged += left[i:]
    merged += right[j:]
    
    return merged, inv_count

# Función para probar con distintos tamaños
def probar_conteo_inversiones():
    
    # Tamaños ajustados para una prueba de rendimiento más rápida y escalable
    tamanios = [1000, 10000, 50000, 100000] 
    
    print("--- Prueba de Rendimiento del Conteo de Inversiones (Merge Sort O(n log n)) ---")
    print(f"{'Tamaño (n)':<12} | {'Inversiones':<15} | {'Tiempo (segundos)':<20}")
    print("---------------------------------------------------------------------")
    
    for n in tamanios:
        # Generar un arreglo con números aleatorios en un rango más contenido (0 a 2n)
        # Esto no cambia la lógica, pero los números generados son más pequeños.
        arr = random.sample(range(n * 2), n) 
        
        inicio = time.time()
        _, inversiones = merge_count(arr)
        fin = time.time()
        
        print(f"{n:<12} | {inversiones:<15} | {fin - inicio:.6f}")

# Ejecución de pruebas
if __name__ == "__main__":
    probar_conteo_inversiones()