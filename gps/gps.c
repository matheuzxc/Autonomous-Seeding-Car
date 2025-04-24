#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "gps.h"

#define UART_NUM UART_NUM_1
#define TXD_PIN 19
#define RXD_PIN 18
#define BUF_SIZE 1024

static const char *TAG = "GPS";

float gps_latitude = 0.0;
float gps_longitude = 0.0;

void gps_init(void) {
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    ESP_LOGI(TAG, "UART GPS inicializado");
}

static float nmea_to_decimal(const char *nmea, const char *direction) {
    if (strlen(nmea) < 4) return 0.0;

    float deg = atof(nmea) / 100.0;
    int d = (int)deg;
    float m = (deg - d) * 100.0;
    float decimal = d + m / 60.0;

    if (direction[0] == 'S' || direction[0] == 'W') {
        decimal *= -1.0;
    }

    return decimal;
}

static void parse_gpgga(char *line) {
    char *token;
    int field = 0;
    char *lat = NULL, *lat_dir = NULL, *lon = NULL, *lon_dir = NULL;

    token = strtok(line, ",");
    while (token != NULL) {
        field++;
        switch (field) {
            case 3: lat = token; break;
            case 4: lat_dir = token; break;
            case 5: lon = token; break;
            case 6: lon_dir = token; break;
        }
        token = strtok(NULL, ",");
    }

    if (lat && lon && lat_dir && lon_dir) {
        gps_latitude = nmea_to_decimal(lat, lat_dir);
        gps_longitude = nmea_to_decimal(lon, lon_dir);
        printf("[GPS] Latitude: %.6f | Longitude: %.6f\n", gps_latitude, gps_longitude);
    }
}

static void gps_task(void *arg) {
    uint8_t data[BUF_SIZE];
    while (1) {
        int len = uart_read_bytes(UART_NUM, data, BUF_SIZE - 1, pdMS_TO_TICKS(1000));
        if (len > 0) {
            data[len] = 0;
            //printf("[GPS RAW] %s\n", data); // mostra tudo recebido
            char *line = strtok((char *)data, "\r\n");
            while (line != NULL) {
                //printf("[DEBUG LINE] %s\n", line); // debug linha por linha
                if (strstr(line, "GGA")) {  // aceita tanto $GPGGA quanto $GNGGA
                    parse_gpgga(line);
                }
                line = strtok(NULL, "\r\n");
            }
        }
    }
}

void gps_start_task(void) {
    xTaskCreate(gps_task, "gps_task", 4096, NULL, 5, NULL);
}

