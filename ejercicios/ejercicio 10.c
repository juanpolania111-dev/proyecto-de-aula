/*
Ejercicio 10: Los sensores analógicos suelen presentar ruido. Definir una lista de 10
lecturas llamada LECTURAS_ADC. Crear un programa que calcule una nueva lista donde cada
elemento sea el promedio de la lectura actual y las dos anteriores (esto se le conoce como
filtro de media móvil). Para la primera posición, segunda y última posición de la nueva
lista, dejar en 0.

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>
int main() {

    float LECTURAS_ADC[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    float FILTRO[10];

    // Primera y segunda posición en 0
    FILTRO[0] = 0;
    FILTRO[1] = 0;

    // Promedio de la lectura actual y las dos anteriores
    for (int i = 2; i < 9; i++) {
        FILTRO[i] = (LECTURAS_ADC[i] +
                     LECTURAS_ADC[i - 1] +
                     LECTURAS_ADC[i - 2]) / 3.0;
    }

    // Última posición en 0
    FILTRO[9] = 0;

    // Mostrar las listas
    printf("LECTURAS_ADC:\n");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", LECTURAS_ADC[i]);
    }

    printf("\n\nFILTRO:\n");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", FILTRO[i]);
    }

    return 0;
}
