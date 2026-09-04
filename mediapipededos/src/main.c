/*
Ejercicio 4.6.4.1: Control de LEDs via MediaPipe y PySerial
Lenguaje: C Puro (ESP-IDF)
Integrantes:
- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
*/

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define UART_PORT UART_NUM_0
#define BUF_SIZE 1024

// 5 pines GPIO asignados a los LEDs
const gpio_num_t leds[5] = {
    GPIO_NUM_18, 
    GPIO_NUM_19, 
    GPIO_NUM_21, 
    GPIO_NUM_22, 
    GPIO_NUM_23
};

void app_main(void) {
    // Configurar pines de los LEDs como salidas
    for (int i = 0; i < 5; i++) {
        gpio_reset_pin(leds[i]);
        gpio_set_direction(leds[i], GPIO_MODE_OUTPUT);
        gpio_set_level(leds[i], 0);
    }

    // Configurar puerto serie UART a 115200 baudios
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

    while (1) {
        // Leer dato recibido desde Python
        int len = uart_read_bytes(UART_PORT, data, BUF_SIZE - 1, 20 / portTICK_PERIOD_MS);

        if (len > 0) {
            data[len] = '\0';
            int cantidad_leds = atoi((char*)data);

            // Encender la cantidad de LEDs recibidos (0 a 5)
            if (cantidad_leds >= 0 && cantidad_leds <= 5) {
                for (int i = 0; i < 5; i++) {
                    if (i < cantidad_leds) {
                        gpio_set_level(leds[i], 1);
                    } else {
                        gpio_set_level(leds[i], 0);
                    }
                }
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}