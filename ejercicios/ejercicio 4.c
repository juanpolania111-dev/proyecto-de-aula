
/*
Ejercicio 1:
Se puede calcular el cuadrado de un número NUMERO al sumar los primeros NUMERO
números impares. Con esta lógica, el cuadrado del número 7 es la sumatoria de los primeros
7 números impares, es decir 1+3+5+7+9+11+13=49. Crear un programa que pida al usuario un número
y se almacene en la variable NUMERO y luego imprima la suma de todos los números impares y
su resultado.
*/
/*# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

int main()
{
    int NUMERO = 5;
    int impar = 1;
    int suma = 0;
    int i;

    printf("Numeros impares: ");

    for(i = 1; i <= NUMERO; i++)
    {
        printf("%d", impar);

        if(i < NUMERO)
        {
            printf(" + ");
        }

        suma = suma + impar;
        impar = impar + 2;
    }

    printf(" = %d\n", suma);

    return 0;
}