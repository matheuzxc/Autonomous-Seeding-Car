#include "gps.hpp"
#include <HardwareSerial.h>
#include <string.h>
#include <stdlib.h>
#include "kalman.hpp"


#define GPS_UART_NUM 1
#define TXD_PIN 19
#define RXD_PIN 18
#define BUF_SIZE 1024


#define FILTER_SIZE 10

static float lat_buffer[FILTER_SIZE] = {0};
static float lon_buffer[FILTER_SIZE] = {0};
static int buffer_index = 0;



static HardwareSerial GPS_UART(GPS_UART_NUM);

static float gps_latitude = 0.0;
static float gps_longitude = 0.0;

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
        float lat_val = nmea_to_decimal(lat, lat_dir);
        float lon_val = nmea_to_decimal(lon, lon_dir);

        // Atualiza buffers circulares
        lat_buffer[buffer_index] = lat_val;
        lon_buffer[buffer_index] = lon_val;
        buffer_index = (buffer_index + 1) % FILTER_SIZE;

        // Calcula médias
        float lat_sum = 0, lon_sum = 0;
        for (int i = 0; i < FILTER_SIZE; i++) {
            lat_sum += lat_buffer[i];
            lon_sum += lon_buffer[i];
        }

        gps_latitude = lat_sum / FILTER_SIZE;
        gps_longitude = lon_sum / FILTER_SIZE;

        Serial.printf("[GPS] Latitude: %.6f | Longitude: %.6f\n", gps_latitude, gps_longitude);
    }

}

static void gps_task(void *arg) {
    static char line_buffer[BUF_SIZE];
    size_t line_pos = 0;

    while (true) {
        while (GPS_UART.available()) {
            char c = GPS_UART.read();
            if (c == '\n' || c == '\r') {
                if (line_pos > 0) {
                    line_buffer[line_pos] = '\0';
                    if (strstr(line_buffer, "GGA")) {
                        parse_gpgga(line_buffer);
                    }
                    line_pos = 0;
                }
            } else {
                if (line_pos < BUF_SIZE - 1) {
                    line_buffer[line_pos++] = c;
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void gps_init() {
    GPS_UART.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN);
    Serial.println("[GPS] UART GPS inicializado");
}

void gps_start_task() {
    xTaskCreatePinnedToCore(
        gps_task,
        "gps_task",
        4096,
        NULL,
        1,
        NULL,
        1 // Core 1
    );
}

float get_latitude() {
    return gps_latitude;
}

float get_longitude() {
    return gps_longitude;
}
