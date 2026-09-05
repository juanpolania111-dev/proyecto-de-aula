/*
Ejercicio 1: Cálculo del Cuadrado vía Terminal Serial
Framework: ESP-IDF (C puro)
Baud rate: 115200

- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
- Alvaro Martinez
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define UART_PORT UART_NUM_0
#define BUF_SIZE 1024

void app_main(void) {
    // Configuración del puerto UART0
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_param_config(UART_PORT, &uart_config);
    uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, NULL, 0);

    uint8_t data[BUF_SIZE];
    
    const char *mensaje_inicio = "\r\n=== EJERCICIO 1: CALCULO DEL CUADRADO ===\r\nIngrese un numero entero: ";
    uart_write_bytes(UART_PORT, mensaje_inicio, strlen(mensaje_inicio));

    while (1) {
        int len = uart_read_bytes(UART_PORT, data, BUF_SIZE - 1, 100 / portTICK_PERIOD_MS);

        if (len > 0) {
            data[len] = '\0';
            
            int numero = atoi((char*)data);
            int cuadrado = numero * numero;

            char respuesta[128];
            snprintf(respuesta, sizeof(respuesta), "\r\nN: %d -> Cuadrado: %d\r\nIngrese otro numero: ", numero, cuadrado);
            uart_write_bytes(UART_PORT, respuesta, strlen(respuesta));
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
