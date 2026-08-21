/*
Ejercicio 7: En sistemas embebidos, los registros suelen empaquetar varios estados. Leer una
variable de 8 bits llamada REGISTRO_ESTADO. El programa debe extraer y mostrar por separado
el valor de los 4 bits menos significativos (nibble inferior) y el estado (0 o 1) del bit
número 5. Usar exclusivamente operadores de bits (&, >>).

# Proyecto de Aula

## Integrantes

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>

int main()
{
    unsigned char REGISTRO_ESTADO;

    scanf("%hhu", &REGISTRO_ESTADO);

    unsigned char nibble_inferior = REGISTRO_ESTADO & 0x0F;
    unsigned char bit_5 = (REGISTRO_ESTADO >> 5) & 0x01;

    printf("Nibble inferior: %u\n", nibble_inferior);
    printf("Bit 5: %u\n", bit_5);

    return 0;
}
