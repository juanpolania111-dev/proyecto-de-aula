/*
Ejercicio 3: Usando NUMERO como limite, aplicar la Criba de Eratostenes e imprimir en
pantalla todos los numeros menores a NUMERO que son primos.

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

int main(void) {
    int NUMERO = 50;
    /* La criba necesita marcar los numeros tachados, por eso el arreglo */
    int tachado[1000];
    int p, multiplo, i, primero;

    if (NUMERO < 2 || NUMERO > 1000) {
        return 0;
    }

    for (i = 0; i < NUMERO; i++) {
        tachado[i] = 0;
    }

    for (p = 2; p * p < NUMERO; p++) {
        if (tachado[p] == 0) {
            /* Se empieza en p*p porque los multiplos menores ya estan tachados */
            for (multiplo = p * p; multiplo < NUMERO; multiplo += p) {
                tachado[multiplo] = 1;
            }
        }
    }

    printf("Números primos menores a %d:\n", NUMERO);
    primero = 1;
    for (i = 2; i < NUMERO; i++) {
        if (tachado[i] == 0) {
            if (primero == 0) {
                printf(" ");
            }
            printf("%d", i);
            primero = 0;
        }
    }
    printf("\n");

    return 0;
}
