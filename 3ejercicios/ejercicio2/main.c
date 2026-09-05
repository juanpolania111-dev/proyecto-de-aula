/*
Ejercicio 2: Caudalímetro y Telemetría Serial (ESP-IDF / FreeRTOS)
- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
- Alvaro Martinez
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define UART_PORT UART_NUM_0
#define BUF_SIZE 1024

// Variables de persistencia para las estadísticas
static int mayor = -1;
static int menor = 100;
static int contador_muestras = 0;
static double suma_total = 0.0;

void app_main(void) {
    // 1. Desinstalar el driver previo de UART0 en caso de estar activo
    uart_driver_delete(UART_PORT);

    // 2. Configuración del puerto UART0
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, NULL, 0));

    uint8_t data[BUF_SIZE];

    while (1) {
        int len = uart_read_bytes(UART_PORT, data, BUF_SIZE - 1, 100 / portTICK_PERIOD_MS);

        if (len > 0) {
            data[len] = '\0'; // Asegurar terminador nulo

            // Buscar la palabra 'caudal' dentro del buffer recibido
            char *ptr = strstr((char*)data, "'caudal':");
            if (ptr == NULL) {
                ptr = strstr((char*)data, "\"caudal\":");
            }

            if (ptr != NULL) {
                int valor_leido = -1;
                // Parsear el número entero después de la clave
                if (sscanf(ptr, "%*[^0123456789]%d", &valor_leido) == 1) {
                    
                    // Validación de rango [0, 99]
                    if (valor_leido >= 0 && valor_leido <= 99) {
                        
                        // Actualizar estadísticas
                        if (contador_muestras == 0 || valor_leido > mayor) {
                            mayor = valor_leido;
                        }
                        if (contador_muestras == 0 || valor_leido < menor) {
                            menor = valor_leido;
                        }
                        
                        contador_muestras++;
                        suma_total += valor_leido;
                        double promedio = suma_total / contador_muestras;

                        // Formatear y transmitir la respuesta por el UART
                        char respuesta[256];
                        snprintf(respuesta, sizeof(respuesta),
                                 "{'ultimo': %d, 'mayor': %d, 'menor': %d, 'promedio': %.2f}\r\n",
                                 valor_leido, mayor, menor, promedio);

                        uart_write_bytes(UART_PORT, respuesta, strlen(respuesta));
                    }
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
