/*
Ejercicio: Preguntar al usuario un número entero y almacenar en la variable NUMERO. 
Imprimir el valor de la posición NUMERO de la secuencia de Fibonacci asumiendo que 
 y. Verificar que NUMERO debe ser >= 2, en caso contrario, mostrar un mensaje que
 NUMERO debe cumplir esa condición.

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

int main()
{
    int NUMERO = 10;
    int f0 = 0;
    int f1 = 1;
    int siguiente;
    int i;

    if(NUMERO < 2)
    {
        printf("NUMERO debe ser mayor o igual a 2.\n");
        return 0;
    }

    for(i = 2; i <= NUMERO; i++)
    {
        siguiente = f0 + f1;
        f0 = f1;
        f1 = siguiente;
    }

    printf("Fibonacci en la posicion %d = %d\n", NUMERO, f1);

    return 0;
}