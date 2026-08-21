/*
Ejercicio 8: Crear una funcion que reciba tres variables booleanas (A, B, C) y retorne el
resultado de la siguiente expresion logica: F = (A . B) + not(C). El resultado debe
mostrarse como una pequena tabla de verdad en la consola para todas las combinaciones
posibles de las entradas.

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

int funcionLogica(int variableA, int variableB, int variableC) {
    return (variableA && variableB) || (!variableC);
}

int main() {
    int variableA, variableB, variableC, F;

    printf(" A B C | F\n");
    printf("-------|---\n");

    for (variableA = 0; variableA <= 1; variableA++) {
        for (variableB = 0; variableB <= 1; variableB++) {
            for (variableC = 0; variableC <= 1; variableC++) {

                F = funcionLogica(variableA, variableB, variableC);

                printf(" %d %d %d | %d\n",
                       variableA, variableB, variableC, F);
            }
        }
    }

    return 0;
}
