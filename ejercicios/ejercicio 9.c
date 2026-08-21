/*
Ejercicio 9: Simular un detector de secuencia para una cerradura electrónica (simulación de
una máquina de estados). El programa debe recibir una lista de bits uno por uno que ingresa
el usuario. Si detecta que los últimos bits ingresados tienen la secuencia específica 1011,
el mensaje debe ser "Cerradura abierta". Si el bit ingresado rompe la secuencia, no debe
mostrar nada.

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

int main()
{
    int bit;
    int estado = 0;

    printf("Detector de secuencia 1011\n");
    printf("Ingrese bits (0 o 1). Ingrese -1 para terminar.\n\n");

    while (1) {
        printf("Ingrese un bit: ");
        scanf("%d", &bit);

        if (bit == -1) {
            break;
        }

        if (bit != 0 && bit != 1) {
            printf("Ingrese solamente 0 o 1.\n");
            continue;
        }

        switch (estado) {

            case 0:
                if (bit == 1) {
                    estado = 1;
                }
                break;

            case 1:
                if (bit == 0) {
                    estado = 2;
                } else {
                    estado = 1;
                }
                break;

            case 2:
                if (bit == 1) {
                    estado = 3;
                } else {
                    estado = 0;
                }
                break;

            case 3:
                if (bit == 1) {
                    estado = 4;
                } else {
                    estado = 2;
                }
                break;
        }

        if (estado == 4) {
            printf("Cerradura abierta\n");

            // Reiniciamos para poder detectar otra secuencia
            estado = 0;
        }
    }

    printf("Programa terminado.\n");

    return 0;
}
