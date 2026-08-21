/*
Ejercicio 2: De un numero entero positivo que esta guardado en una variable llamada NUMERO,
mostrar en pantalla su raiz cuadrada usando el metodo de Newton. Debe realizarse una funcion
que acepte el valor de NUMERO y retorne el resultado, sin usar una libreria que contenga esa
funcion. Resultado esperado: {'Numero' : NUMERO, 'Raiz cuadrada usando Newton' : RESULTADO}

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

/* Newton: x = (x + N/x) / 2, repetido hasta que el valor se estabiliza */
double raizNewton(int numero) {
    double x = numero;
    int i;

    for (i = 0; i < 30; i++) {
        x = (x + numero / x) / 2.0;
    }

    return x;
}

int main(void) {
    int NUMERO = 625;
    double RESULTADO;

    if (NUMERO <= 0) {
        return 0;
    }

    RESULTADO = raizNewton(NUMERO);

    printf("{'Número' : %d, 'Raíz cuadrada usando Newton' : %.6f}\n", NUMERO, RESULTADO);

    return 0;
}
