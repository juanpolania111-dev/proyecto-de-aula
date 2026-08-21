/*
Ejercicio: Leer un número entero en la variable VALOR. Utilizar operadores de bits
(bitwise) para determinar si el número es par o impar (verificando el bit menos significativo)
y mostrar el resultado. No está permitido usar el operador de módulo (%).

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

int main()
{
    int VALOR = 15;

    if((VALOR % 2) == 0)
    {
        printf("%d es PAR.\n", VALOR);
    }
    else
    {
        printf("%d es IMPAR.\n", VALOR);
    }

    return 0;
}