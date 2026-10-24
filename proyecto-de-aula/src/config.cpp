/* Configuration options for esp32-weather-epd.
 * Copyright (C) 2022-2025 Luke Marzen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <Arduino.h>
#include "config.h"

// PINS (Ajustados para ESP32 Generico)
const uint8_t PIN_BAT_ADC  = 34; 
const uint8_t PIN_EPD_BUSY = 14; 
const uint8_t PIN_EPD_CS   = 13;
const uint8_t PIN_EPD_RST  = 21;
const uint8_t PIN_EPD_DC   = 22;
const uint8_t PIN_EPD_SCK  = 18;
const uint8_t PIN_EPD_MISO = 19; 
const uint8_t PIN_EPD_MOSI = 23;
const uint8_t PIN_EPD_PWR  = 26; 

// I2C Pins used for BME280
const uint8_t PIN_BME_SDA = 17;
const uint8_t PIN_BME_SCL = 16;
const uint8_t PIN_BME_PWR = 4;   
const uint8_t BME_ADDRESS = 0x76; 

// WIFI
const char *WIFI_SSID     = "FLIA-RAMIREZ_2.4";
const char *WIFI_PASSWORD = "22461272";
const unsigned long WIFI_TIMEOUT = 10000; // ms

// HTTP
const unsigned HTTP_CLIENT_TCP_TIMEOUT = 10000; // ms

// OPENWEATHERMAP API
const String OWM_APIKEY   = "baf1d26a2a85c1670dbe7c3732a6e8f8";
const String OWM_ENDPOINT = "api.openweathermap.org";
const String OWM_ONECALL_VERSION = "3.0";
const String OWM_UNITS = "metric";

// LOCATION (Soledad / Barranquilla, Atlantico)
const String LAT = "10.9685";
const String LON = "-74.7813";
const String CITY_STRING = "Barranquilla";

// TIME (Colombia COT5)
const char *TIMEZONE = "COT5";

// Time and Date Formats
const char *TIME_FORMAT = "%H:%M";      // Formato 24 Horas
const char *HOUR_FORMAT = "%H";         // Formato de horas para grafica
const char *DATE_FORMAT = "%a, %B %e";  
const char *REFRESH_TIME_FORMAT = "%x %H:%M";

// NTP Time Servers
const char *NTP_SERVER_1 = "pool.ntp.org";
const char *NTP_SERVER_2 = "time.nist.gov";
const unsigned long NTP_TIMEOUT = 20000; // ms

// SLEEP & POWER
const int SLEEP_DURATION = 4; // Se actualiza cada 4 minutos (240 segundos)

// Ahorro de energia nocturno
const int BED_TIME  = 00; // Ultima actualizacion a las 00:00 (Medianoche)
const int WAKE_TIME = 05; // Despierta a las 05:00 AM

// HOURLY OUTLOOK GRAPH
const int HOURLY_GRAPH_MAX = 24; // Muestra grafica de las proximas 24 horas

// BATTERY THRESHOLDS (mV)
const uint32_t WARN_BATTERY_VOLTAGE     = 3535; 
const uint32_t LOW_BATTERY_VOLTAGE      = 3462; 
const uint32_t VERY_LOW_BATTERY_VOLTAGE = 3442; 
const uint32_t CRIT_LOW_BATTERY_VOLTAGE = 3404; 
const unsigned long LOW_BATTERY_SLEEP_INTERVAL      = 30;  
const unsigned long VERY_LOW_BATTERY_SLEEP_INTERVAL = 120; 
const uint32_t MAX_BATTERY_VOLTAGE = 4200; 
const uint32_t MIN_BATTERY_VOLTAGE = 3000;