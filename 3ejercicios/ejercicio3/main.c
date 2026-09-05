/*
  Actividad 4.7.6.3: Analizar trama en JSON
  Framework: ESP-IDF 
- Juan Polania
- Jurgen Cantillo
- Giovani Pedroza
- Alvaro Martinez
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define UART_PORT UART_NUM_0
#define BUF_SIZE 1024

// Función auxiliar para buscar el valor de una clave en el texto JSON
bool obtener_valor_clave(const char *json, const char *clave, char *out_val, size_t max_len) {
    char patron[64];
    // Buscar la clave entre comillas dobles o sencillas
    snprintf(patron, sizeof(patron), "\"%s\":", clave);
    char *ptr = strstr(json, patron);
    if (!ptr) {
        snprintf(patron, sizeof(patron), "'%s':", clave);
        ptr = strstr(json, patron);
    }
    
    if (!ptr) return false; // Clave no encontrada

    ptr = strchr(ptr, ':');
    if (!ptr) return false;
    ptr++; // Avanzar después de ':'

    // Saltar espacios en blanco
    while (*ptr == ' ' || *ptr == '\t') ptr++;

    // Extraer valor
    int i = 0;
    if (*ptr == '"' || *ptr == '\'') { // Valor de tipo String
        char comilla = *ptr;
        ptr++;
        while (*ptr && *ptr != comilla && i < max_len - 1) {
            out_val[i++] = *ptr++;
        }
    } else { // Valor de tipo Númerico
        while (*ptr && (isdigit((unsigned char)*ptr) || *ptr == '.' || *ptr == '-') && i < max_len - 1) {
            out_val[i++] = *ptr++;
        }
    }
    out_val[i] = '\0';

    return (i > 0);
}

// Comprueba si un texto es un número válido (int o float)
bool es_numero_valido(const char *str) {
    if (str == NULL || *str == '\0') return false;
    char *endptr;
    strtod(str, &endptr);
    return (*endptr == '\0');
}

void procesar_trama_json(const char *buffer) {
    char id[64] = {0};
    char temp_str[32] = {0};
    char hum_str[32] = {0};
    char dist_str[32] = {0};

    // 1. Validar presencia de las 4 claves obligatorias
    bool tiene_id = obtener_valor_clave(buffer, "ID", id, sizeof(id));
    bool tiene_temp = obtener_valor_clave(buffer, "Temperatura", temp_str, sizeof(temp_str));
    bool tiene_hum = obtener_valor_clave(buffer, "Humedad", hum_str, sizeof(hum_str));
    bool tiene_dist = obtener_valor_clave(buffer, "Distancia", dist_str, sizeof(dist_str));

    if (!tiene_id || !tiene_temp || !tiene_hum || !tiene_dist) {
        char err[128];
        snprintf(err, sizeof(err), "ERROR: Trama incompleta. Faltan claves obligatorias.\r\n");
        uart_write_bytes(UART_PORT, err, strlen(err));
        return;
    }

    // 2. Validar tipos de datos (ID es string, los demás números)
    if (!es_numero_valido(temp_str) || !es_numero_valido(hum_str) || !es_numero_valido(dist_str)) {
        // Si hay error de tipo, la guía especifica que la trama se ignora por completo
        return;
    }

    float temperatura = atof(temp_str);
    float humedad = atof(hum_str);
    float distancia = atof(dist_str);

    // 3. Imprimir por puerto serie las 4 claves procesadas
    char respuesta[256];
    snprintf(respuesta, sizeof(respuesta),
             "DATOS RECIBIDOS -> ID: %s | Temperatura: %.2f | Humedad: %.2f | Distancia: %.2f\r\n",
             id, temperatura, humedad, distancia);

    uart_write_bytes(UART_PORT, respuesta, strlen(respuesta));
}

void app_main(void) {
    uart_driver_delete(UART_PORT);

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
        int len = uart_read_bytes(UART_PORT, data, BUF_SIZE - 1, pdMS_TO_TICKS(100));

        if (len > 0) {
            data[len] = '\0';
            procesar_trama_json((char*)data);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
